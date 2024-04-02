#include "luxlab/raw_image.hpp"

#include <fmt/format.h>

#include <fstream>

namespace luxlab {

RawImage::RawImage(const std::filesystem::path& file_path) {
    // check if file exists
    if (!std::filesystem::exists(file_path)) {
        fmt::print("ERROR: file {} does not exist\n", file_path.string());
        std::terminate();
    }

    // check if file is a regular file
    if (!std::filesystem::is_regular_file(file_path)) {
        fmt::print("ERROR: {} is not a regular file\n", file_path.string());
        std::terminate();
    }

    // open file
    m_path = file_path;
    std::ifstream file(file_path.string(), std::ios::binary);

    // get file size
    file.seekg(0, std::ios::end);
    int length = file.tellg();

    // allocate data buffer
    m_data.resize(length);

    // read file into buffer
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(m_data.data()), length);
    m_data.resize(file.tellg());

    // initialize header
    m_header = TIFFHeader{m_data};

    // initialize ifds
    uint32_t offset = m_header.offset();
    int ifd_counter = 0;
    while (offset != 0) {
        // create IFD
        IFD ifd{ifd_counter++, m_data, offset, m_header.byte_order()};
        m_ifds.push_back(ifd);

        // get next IFD offset
        offset = m_header.byte_order().calculate<uint32_t>(
            {m_data.begin() + offset + ifd.size(), 4});
    }
}

void RawImage::dump_hex() const {
    // create hex file path from image file path
    std::filesystem::path hex_file = m_path;
    hex_file.replace_extension(".hex");

    // open hex file
    std::ofstream file(hex_file.string(), std::ios::trunc);

    // write header
    file << fmt::format(
        "Offset      _0 _1 _2 _3 _4 _5 _6 _7 _8 _9 _A _B _C _D _E _F\n\n");

    // write hex dump
    int line_counter = 0;
    int counter16 = 0;
    std::string hex;
    std::string ascii;
    for (const auto& byte : m_data) {
        // get value of next byte
        int value = static_cast<int>(byte);

        // format hex string
        hex += fmt::format("{:02x} ", value);

        // convert value to ascii if printable, otherwise use '.'
        ascii += fmt::format(
            "{}", (value >= 32 && value <= 126) ? static_cast<char>(value) : '.');

        // increment the 16 byte counter
        counter16++;

        // if 16 bytes have been read
        if (counter16 >= 16) {
            // get line offset
            std::string offset = fmt::format("0x{:08X}", line_counter * 16);
            offset.back() = '_';

            // write line to file
            file << fmt::format("{}  {} {}\n", offset, hex, ascii);

            // clear strings and reset counter
            hex.clear();
            ascii.clear();
            counter16 = 0;

            // increment line counter
            ++line_counter;
        }
    }
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::RawImage>::format(
    const luxlab::RawImage& raw_image, format_context& ctx) const {
    std::string str = "";
    str += fmt::format("Raw image\n");
    str += fmt::format("|    Path: {}\n", raw_image.path().string());
    str += fmt::format("|    Size: {} bytes\n", raw_image.size());
    str += fmt::format("{:1}\n", raw_image.header());
    for (const auto& ifd : raw_image.ifds()) {
        str += fmt::format("{:1}\n", ifd);
    }
    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt

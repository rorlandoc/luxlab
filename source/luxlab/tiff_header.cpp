#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "luxlab/tiff_header.hpp"

namespace luxlab {

TIFFHeader::TIFFHeader(const std::vector<std::byte>& data) {
    // Header is 8 bytes long
    // 2 bytes to indicate byte order
    // 2 bytes with a magic number
    // 4 bytes with the offset to the first IFD
    if (!(data.size() >= 8)) {
        fmt::print(
            "ERROR: TIFF header is too short\n"
            "Expected at least 8 bytes, got {}\n",
            data.size());
        std::terminate();
    }

    // get handle of first byte
    auto current_byte = data.begin();

    // get byte order
    int byte_order =
        (static_cast<int>(*current_byte) << 8) + static_cast<int>(*(current_byte + 1));
    if (byte_order == ByteOrder::LITTLE_ENDIAN) {
        m_byte_order = ByteOrder{ByteOrder::LITTLE_ENDIAN};
    } else if (byte_order == ByteOrder::BIG_ENDIAN) {
        m_byte_order = ByteOrder{ByteOrder::BIG_ENDIAN};
    } else {
        fmt::print("ERROR: unknown byte order\n");
        std::terminate();
    }
    std::advance(current_byte, 2);

    // verify byte ordering with magic number
    int magic_number = m_byte_order.calculate({current_byte, 2});
    if (magic_number != 0x002a) {
        fmt::print("ERROR: unable to verify byte ordering\n");
        std::terminate();
    }
    std::advance(current_byte, 2);

    // get offset to first IFD
    m_offset = m_byte_order.calculate({current_byte, 4});
}

void to_json(nlohmann::json& j, const TIFFHeader& header) {
    j = nlohmann::json{{"byte_order", header.byte_order()},
                       {"offset", fmt::format("0x{:08X}", header.offset())}};
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::TIFFHeader>::format(
    const luxlab::TIFFHeader& header, format_context& ctx) const {
    std::string pad = "";
    for (int i = 0; i < m_padding; ++i) {
        pad += "|  ";
    }

    std::string str = "";
    str += pad;
    str += "TIFF header:";
    str += "\n" + pad;
    str += "|  Byte order: ";
    str += fmt::format("{}", header.byte_order());
    str += "\n" + pad;
    str += "|  Offset to first IFD: 0x";
    str += fmt::format("{:08X}", header.offset());

    return fmt::format_to(ctx.out(), "{}", str);
}

}  // namespace fmt

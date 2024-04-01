#include "luxlab/ifd.hpp"

#include <fmt/format.h>

namespace luxlab {

IFD::IFD(int id, std::span<std::byte> data, int offset, ByteOrder byte_order)
    : m_id(id), m_offset(offset), m_byte_order(byte_order) {
    // get handle to start of IFD section
    auto current_byte = data.begin() + offset;

    // IFD section needs to be at least 2 bytes long
    if (std::distance(current_byte, data.end()) < 2) {
        fmt::print("ERROR: IFD data buffer is too small\n");
        std::terminate();
    }

    // get number of entries
    int num_entries = m_byte_order.calculate({current_byte, 2});
    current_byte += 2;

    // IFD section needs to be at least 12 bytes long per entry
    if (std::distance(current_byte, data.end()) < 12 * num_entries) {
        fmt::print("ERROR: IFD data buffer is too small\n");
        std::terminate();
    }

    // get entries
    for (int ientry = 0; ientry < num_entries; ++ientry) {
        DirectoryEntry entry{{current_byte, 12}, m_byte_order};
        if (entry.has_offset()) {
            auto offset = std::get<uint32_t>(entry.values()[0]);
            entry.initialize_value(
                {data.begin() + offset, static_cast<size_t>(entry.data_size())});
        }
        m_entries[entry.tag()] = entry;
        current_byte += 12;
    }
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::IFD>::format(const luxlab::IFD &ifd,
                                                        format_context &ctx) const {
    std::string pad = "";
    for (int i = 0; i < m_padding; ++i) {
        pad += "|    ";
    }

    std::string str = "";
    str += pad;
    str += fmt::format("IFD {} [{} entries]", ifd.id(), ifd.num_entries());

    std::string tag_fmt = "{:" + fmt::format("{}", m_padding + 1) + "}";
    for (const auto &[_, tag] : ifd.entries()) {
        str += fmt::format(fmt::runtime(tag_fmt), tag);
    }

    return format_to(ctx.out(), "{}", str);
}

}  // namespace fmt
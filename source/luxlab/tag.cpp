#include "luxlab/tag.hpp"

#include <fmt/format.h>

namespace luxlab {

Tag::Tag(std::span<std::byte> data, ByteOrder byte_order) : m_byte_order(byte_order) {
    // Tag layout:
    // 2 bytes: tag id
    // 2 bytes: data format
    // 4 bytes: number of components
    // 4 bytes: data offset or value

    // buffer needs to be at least 12 bytes long
    if (data.size() < 12) {
        fmt::print("ERROR: Tag data buffer is too small\n");
        std::terminate();
    }

    // get tag type
    m_type = TagType{m_byte_order.calculate({data.begin(), 2})};
    auto current_byte = data.begin() + 2;

    // get data format
    m_format = TagDataFormat{m_byte_order.calculate({current_byte, 2})};
    current_byte += 2;

    // get number of components
    m_components = m_byte_order.calculate({current_byte, 4});
    current_byte += 4;

    // get data offset or value
    m_value = m_byte_order.calculate({current_byte, 4});
    current_byte += 4;
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::Tag>::format(const luxlab::Tag &tag,
                                                        format_context &ctx) const {
    std::string pad = "";
    for (int i = 0; i < m_padding; ++i) {
        pad += "|    ";
    }

    return format_to(ctx.out(),
                     "{}[ 0x{:04X} ][ {:<28} ][ {:<17} ][ {:>6d} ][ {:>6d} ][ 0x{:08x} ]",
                     pad, tag.type_id(), tag.type(), tag.format(), tag.components(),
                     tag.data_size(), tag.value());
}

}  // namespace fmt
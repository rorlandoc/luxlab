#include "luxlab/byte_order.hpp"

#include <fmt/format.h>

namespace luxlab {

int ByteOrder::calculate(std::span<const std::byte> data) {
    int value = 0;
    if (m_endianness == Endianness::LITTLE_ENDIAN) {
        int shift = 0;
        for (const auto& byte : data) {
            value += static_cast<int>(byte) << shift;
            shift += 8;
        }
    } else {
        int shift = (data.size() - 1) * 8;
        for (const auto& byte : data) {
            value += static_cast<int>(byte) << shift;
            shift -= 8;
        }
    }
    return value;
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::ByteOrder>::format(
    const luxlab::ByteOrder& byte_order, format_context& ctx) const {
    std::string str = "Unknown";
    switch (byte_order) {
        case luxlab::ByteOrder::LITTLE_ENDIAN:
            str = "Little endian";
            break;
        case luxlab::ByteOrder::BIG_ENDIAN:
            str = "Big endian";
            break;
    }
    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt
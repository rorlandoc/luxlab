#include "luxlab/byte_order.hpp"

#include <fmt/format.h>

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
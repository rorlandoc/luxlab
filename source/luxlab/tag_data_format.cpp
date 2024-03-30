#include "luxlab/tag_data_format.hpp"

#include <fmt/format.h>

namespace fmt {

format_context::iterator formatter<luxlab::TagDataFormat>::format(
    const luxlab::TagDataFormat& tag_data_format, format_context& ctx) const {
    std::string str = "Unknown";

    switch (tag_data_format) {
        case luxlab::TagDataFormat::UNSIGNED_BYTE:
            str = "Unsigned byte";
            break;
        case luxlab::TagDataFormat::ASCII_STRING:
            str = "ASCII string";
            break;
        case luxlab::TagDataFormat::UNSIGNED_SHORT:
            str = "Unsigned short";
            break;
        case luxlab::TagDataFormat::UNSIGNED_LONG:
            str = "Unsigned long";
            break;
        case luxlab::TagDataFormat::UNSIGNED_RATIONAL:
            str = "Unsigned rational";
            break;
        case luxlab::TagDataFormat::SIGNED_BYTE:
            str = "Signed byte";
            break;
        case luxlab::TagDataFormat::UNDEFINED:
            str = "Undefined";
            break;
        case luxlab::TagDataFormat::SIGNED_SHORT:
            str = "Signed short";
            break;
        case luxlab::TagDataFormat::SIGNED_LONG:
            str = "Signed long";
            break;
        case luxlab::TagDataFormat::SIGNED_RATIONAL:
            str = "Signed rational";
            break;
        case luxlab::TagDataFormat::FLOAT:
            str = "Float";
            break;
        case luxlab::TagDataFormat::DOUBLE:
            str = "Double";
            break;
    }
    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt
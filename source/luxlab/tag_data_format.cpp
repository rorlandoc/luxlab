#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "luxlab/tag_data_format.hpp"

namespace luxlab {

void to_json(nlohmann::json &j, const TagDataFormat &format) {
    j = fmt::format("{}", format);
}

void to_json(nlohmann::json &j, const TagValue &value) {
    std::visit([&j](const auto &v) { j = v; }, value);
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::TagDataFormat>::format(
    const luxlab::TagDataFormat &tag_data_format, format_context &ctx) const {
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

format_context::iterator formatter<luxlab::TagValue>::format(
    const luxlab::TagValue &tag_value, format_context &ctx) const {
    std::string str = "Unknown";

    if (std::holds_alternative<uint8_t>(tag_value)) {
        auto val = std::get<uint8_t>(tag_value);
        str = fmt::format("0x{:02X}", val);
    } else if (std::holds_alternative<std::string>(tag_value)) {
        auto val = std::get<std::string>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<uint16_t>(tag_value)) {
        auto val = std::get<uint16_t>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<uint32_t>(tag_value)) {
        auto val = std::get<uint32_t>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<luxlab::UnsignedRational>(tag_value)) {
        auto val = std::get<luxlab::UnsignedRational>(tag_value);
        str = fmt::format("{}/{}", val.numerator, val.denominator);
    } else if (std::holds_alternative<int8_t>(tag_value)) {
        auto val = std::get<int8_t>(tag_value);
        str = fmt::format("0x{:02x}", val);
    } else if (std::holds_alternative<std::byte>(tag_value)) {
        auto val = std::get<std::byte>(tag_value);
        str = fmt::format("0x{:02X}", static_cast<int>(val));
    } else if (std::holds_alternative<int16_t>(tag_value)) {
        auto val = std::get<int16_t>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<int32_t>(tag_value)) {
        auto val = std::get<int32_t>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<luxlab::SignedRational>(tag_value)) {
        auto val = std::get<luxlab::SignedRational>(tag_value);
        str = fmt::format("{}/{}", val.numerator, val.denominator);
    } else if (std::holds_alternative<float>(tag_value)) {
        auto val = std::get<float>(tag_value);
        str = fmt::format("{}", val);
    } else if (std::holds_alternative<double>(tag_value)) {
        auto val = std::get<double>(tag_value);
        str = fmt::format("{}", val);
    }

    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt
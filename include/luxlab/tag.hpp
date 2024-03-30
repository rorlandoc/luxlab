#ifndef LUXLAB_TAG_HPP
#define LUXLAB_TAG_HPP

#include <fmt/core.h>

#include <array>
#include <cstddef>
#include <span>

#include "luxlab/byte_order.hpp"
#include "luxlab/tag_data_format.hpp"
#include "luxlab/tag_type.hpp"

namespace luxlab {

class Tag {
   public:
    Tag() = default;
    Tag(std::span<std::byte> data, ByteOrder byte_order);

    inline TagType type() const { return m_type; }
    inline int type_id() const { return m_type.id(); }

    inline TagDataFormat format() const { return m_format; };
    inline int format_id() const { return m_format.id(); }

    inline int components() const { return m_components; }
    inline int data_size() const { return m_components * m_format.size(); }
    inline int value() const { return m_value; }

   private:
    ByteOrder m_byte_order;
    TagType m_type;
    TagDataFormat m_format;
    int m_components;
    int m_value;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::Tag> {
    constexpr auto parse(format_parse_context &ctx) {
        auto i = ctx.begin();
        auto end = ctx.end();
        if (i != end && (*i == '1' || *i == '2' || *i == '3' || *i == '4' || *i == '5' ||
                         *i == '6' || *i == '7' || *i == '8' || *i == '9')) {
            m_padding = *i++ - '0';
        }
        if (i != end && *i != '}') {
            throw format_error("invalid format");
        }
        return i;
    }

    format_context::iterator format(const luxlab::Tag &tag, format_context &ctx) const;

   private:
    int m_padding = 0;
};

}  // namespace fmt

#endif

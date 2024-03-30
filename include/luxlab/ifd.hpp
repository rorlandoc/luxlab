#ifndef LUXLAB_IFD_HPP
#define LUXLAB_IFD_HPP

#include <fmt/core.h>

#include <cstddef>
#include <map>
#include <span>

#include "luxlab/byte_order.hpp"
#include "luxlab/tag.hpp"

namespace luxlab {

class IFD {
   public:
    IFD() = default;
    IFD(int id, std::span<std::byte> data, int offset, ByteOrder byte_order);

    const std::map<TagType, Tag> &tags() const { return m_tags; }
    std::map<TagType, Tag> &tags() { return m_tags; }

    int id() const { return m_id; }
    int offset() const { return m_id; }
    int num_entries() const { return m_tags.size(); }

   private:
    int m_id;
    int m_offset;
    ByteOrder m_byte_order;
    std::map<TagType, Tag> m_tags;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::IFD> {
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

    format_context::iterator format(const luxlab::IFD &ifd, format_context &ctx) const;

   private:
    int m_padding = 0;
};

}  // namespace fmt

#endif  // !LUXLAB_IFD_HPP
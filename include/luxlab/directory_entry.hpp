#ifndef LUXLAB_DIRECTORY_ENTRY_HPP
#define LUXLAB_DIRECTORY_ENTRY_HPP

#include <fmt/core.h>

#include <array>
#include <cstddef>
#include <span>
#include <vector>

#include "luxlab/byte_order.hpp"
#include "luxlab/tag.hpp"
#include "luxlab/tag_data_format.hpp"

namespace luxlab {

class DirectoryEntry {
   public:
    DirectoryEntry() = default;
    DirectoryEntry(std::span<std::byte> data, ByteOrder byte_order);

    inline Tag tag() const { return m_tag; }
    inline int tag_id() const { return m_tag.id(); }

    inline TagDataFormat format() const { return m_format; };
    inline int format_id() const { return m_format.id(); }

    inline int components() const { return m_components; }
    inline int data_size() const { return m_components * m_format.size(); }
    inline const std::vector<TagValue> &values() const { return m_values; }

    inline bool has_offset() const { return m_offset; }
    void initialize_value(std::span<std::byte> data);

   private:
    ByteOrder m_byte_order;
    Tag m_tag;
    TagDataFormat m_format;
    int m_components;
    bool m_offset;
    std::vector<TagValue> m_values;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::DirectoryEntry> {
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

    format_context::iterator format(const luxlab::DirectoryEntry &entry,
                                    format_context &ctx) const;

   private:
    int m_padding = 0;
};

}  // namespace fmt

#endif  // !LUXLAB_DIRECTORY_ENTRY_HPP

#ifndef LUXLAB_IFD_HPP
#define LUXLAB_IFD_HPP

#include <fmt/core.h>

#include <cstddef>
#include <map>
#include <memory>
#include <span>

#include "luxlab/byte_order.hpp"
#include "luxlab/directory_entry.hpp"

namespace luxlab {

class IFD {
   public:
    IFD() = default;
    IFD(int id, std::span<std::byte> data, uint32_t offset, ByteOrder byte_order);

    const std::map<Tag, DirectoryEntry> &entries() const { return m_entries; }
    std::map<Tag, DirectoryEntry> &entries() { return m_entries; }

    inline int id() const { return m_id; }
    inline int offset() const { return m_id; }
    inline int num_entries() const { return m_entries.size(); }
    inline size_t size() const { return 2 + 12 * m_entries.size(); }

   private:
    int m_id;
    int m_offset;
    ByteOrder m_byte_order;
    std::map<Tag, DirectoryEntry> m_entries;
    std::map<Tag, std::shared_ptr<IFD>> m_sub_ifds;
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
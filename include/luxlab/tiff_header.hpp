#ifndef LUXLAB_TIFF_HEADER_HPP
#define LUXLAB_TIFF_HEADER_HPP

#include <fmt/core.h>

#include <cstddef>
#include <vector>

#include "luxlab/byte_order.hpp"

namespace luxlab {

class TIFFHeader {
   public:
    TIFFHeader() = default;
    TIFFHeader(const std::vector<std::byte>& data);

    inline ByteOrder byte_order() const { return m_byte_order; }
    inline uint32_t offset() const { return m_offset; }

   private:
    ByteOrder m_byte_order;
    uint32_t m_offset;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::TIFFHeader> {
    constexpr auto parse(format_parse_context& ctx) {
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

    format_context::iterator format(const luxlab::TIFFHeader& header,
                                    format_context& ctx) const;

   private:
    int m_padding = 0;
};

}  // namespace fmt

#endif  // !LUXLAB_TIFF_HEADER_HPP
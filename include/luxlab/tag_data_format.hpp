#ifndef LUXLAB_TAG_DATA_FORMAT_HPP
#define LUXLAB_TAG_DATA_FORMAT_HPP

#include <fmt/core.h>

#include <array>

namespace luxlab {

class TagDataFormat {
   public:
    enum Format : int {
        UNSIGNED_BYTE = 1,
        ASCII_STRING = 2,
        UNSIGNED_SHORT = 3,
        UNSIGNED_LONG = 4,
        UNSIGNED_RATIONAL = 5,
        SIGNED_BYTE = 6,
        UNDEFINED = 7,
        SIGNED_SHORT = 8,
        SIGNED_LONG = 9,
        SIGNED_RATIONAL = 10,
        FLOAT = 11,
        DOUBLE = 12
    };

    TagDataFormat() : m_format(UNDEFINED) {}
    constexpr TagDataFormat(Format format) : m_format(format) {}
    constexpr explicit TagDataFormat(int format)
        : m_format(static_cast<Format>(format)) {}

    constexpr operator Format() const { return m_format; }
    explicit operator bool() = delete;

    constexpr int id() const { return static_cast<int>(m_format); }
    constexpr int size() const { return format_sizes[m_format]; }

   private:
    Format m_format;
    constexpr static std::array<int, 12> format_sizes = {1, 1, 2, 4, 8, 1,
                                                         1, 2, 4, 8, 4, 8};
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::TagDataFormat> : formatter<std::string> {
    format_context::iterator format(const luxlab::TagDataFormat &format,
                                    format_context &ctx) const;
};

}  // namespace fmt

#endif  // ! LUXLAB_DATA_FORMAT_HPP

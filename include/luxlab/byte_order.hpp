#ifndef LUXLAB_BYTE_ORDER_HPP
#define LUXLAB_BYTE_ORDER_HPP

#include <fmt/core.h>

#include <cstddef>
#include <span>

namespace luxlab {

class ByteOrder {
   public:
    enum Endianness : int { LITTLE_ENDIAN = 0x4949, BIG_ENDIAN = 0x4D4D };

    ByteOrder() = default;
    constexpr ByteOrder(Endianness endianness) : m_endianness(endianness) {}

    constexpr operator Endianness() const { return m_endianness; }
    explicit operator bool() = delete;

    constexpr int id() const { return static_cast<int>(m_endianness); }

    int calculate(std::span<const std::byte> data);

   private:
    Endianness m_endianness;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::ByteOrder> : formatter<std::string> {
    format_context::iterator format(const luxlab::ByteOrder& byte_order,
                                    format_context& ctx) const;
};

}  // namespace fmt

#endif  // !LUXLAB_BYTE_ORDER_HPP
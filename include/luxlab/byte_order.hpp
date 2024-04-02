#ifndef LUXLAB_BYTE_ORDER_HPP
#define LUXLAB_BYTE_ORDER_HPP

#include <algorithm>
#include <bit>
#include <cstddef>
#include <span>

#include <fmt/core.h>
#include <nlohmann/json.hpp>

namespace luxlab {

class ByteOrder {
   public:
    enum Endianness : int { LITTLE_ENDIAN = 0x4949, BIG_ENDIAN = 0x4D4D };

    ByteOrder() = default;
    constexpr ByteOrder(Endianness endianness) : m_endianness(endianness) {}

    constexpr operator Endianness() const { return m_endianness; }
    explicit operator bool() = delete;

    constexpr int id() const { return static_cast<int>(m_endianness); }

    template <typename T = int>
    T calculate(std::span<const std::byte> data) {
        T value = T{};
        if (m_endianness == Endianness::LITTLE_ENDIAN) {
            int shift = 0;
            for (const auto& byte : data) {
                value += (static_cast<T>(byte) << shift);
                shift += 8;
            }
        } else {
            int shift = (data.size() - 1) * 8;
            for (const auto& byte : data) {
                value += (static_cast<T>(byte) << shift);
                shift -= 8;
            }
        }
        return value;
    }

    template <>
    std::string calculate(std::span<const std::byte> data) {
        std::string value = "";
        if (m_endianness == Endianness::LITTLE_ENDIAN) {
            for (const auto& byte : data) {
                char c = static_cast<char>(byte);
                if (c == '\0') {
                    break;
                }
                value += fmt::format("{}", c);
            }
        } else {
            for (const auto& byte : data) {
                char c = static_cast<char>(byte);
                if (c == '\0') {
                    break;
                }
                value += fmt::format("{:c}", byte);
            }
            std::reverse(value.begin(), value.end());
        }
        return value;
    }

    template <>
    float calculate(std::span<const std::byte> data) {
        return std::bit_cast<float>(calculate<uint32_t>(data));
    }

    template <>
    double calculate(std::span<const std::byte> data) {
        return std::bit_cast<double>(calculate<uint64_t>(data));
    }

   private:
    Endianness m_endianness;
};

void to_json(nlohmann::json& j, const ByteOrder& byte_order);

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::ByteOrder> : formatter<std::string> {
    format_context::iterator format(const luxlab::ByteOrder& byte_order,
                                    format_context& ctx) const;
};

}  // namespace fmt

#endif  // !LUXLAB_BYTE_ORDER_HPP
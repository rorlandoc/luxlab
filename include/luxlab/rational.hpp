#ifndef LUXLAB_RATIONAL_HPP
#define LUXLAB_RATIONAL_HPP

#include <cstddef>
#include <cstdint>
#include <span>
#include <string>
#include <type_traits>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "luxlab/byte_order.hpp"

namespace luxlab {

template <typename T>
struct Rational {
    T numerator;
    T denominator;

    Rational() = default;
    Rational(std::span<std::byte> data, ByteOrder byte_order) {
        // The data is expected to be 8 bytes long.
        if (data.size() != 8) {
            fmt::print("Invalid rational data size: {} (expected 8 bytes)\n",
                       data.size());
            std::terminate();
        }

        switch (byte_order) {
            case ByteOrder::LITTLE_ENDIAN:
                numerator =
                    (static_cast<T>(data[0]) << 0) + (static_cast<T>(data[1]) << 8) +
                    (static_cast<T>(data[2]) << 16) + (static_cast<T>(data[3]) << 24);
                denominator =
                    (static_cast<T>(data[4]) << 0) + (static_cast<T>(data[5]) << 8) +
                    (static_cast<T>(data[6]) << 16) + (static_cast<T>(data[7]) << 24);
                break;
            case ByteOrder::BIG_ENDIAN:
                numerator =
                    (static_cast<T>(data[3]) << 0) + (static_cast<T>(data[2]) << 8) +
                    (static_cast<T>(data[1]) << 16) + (static_cast<T>(data[0]) << 24);
                denominator =
                    (static_cast<T>(data[7]) << 0) + (static_cast<T>(data[6]) << 8) +
                    (static_cast<T>(data[5]) << 16) + (static_cast<T>(data[4]) << 24);
                break;
        }
    }
};

using UnsignedRational = Rational<uint32_t>;
using SignedRational = Rational<int32_t>;

template <typename T>
void to_json(nlohmann::json& j, const Rational<T>& r) {
    j = fmt::format("{}/{}", r.numerator, r.denominator);
}

}  // namespace luxlab

#endif  // !LUXLAB_RATIONAL_HPP
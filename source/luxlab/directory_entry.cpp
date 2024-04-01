#include "luxlab/directory_entry.hpp"

#include <fmt/format.h>

namespace luxlab {

DirectoryEntry::DirectoryEntry(std::span<std::byte> data, ByteOrder byte_order)
    : m_byte_order(byte_order) {
    // DirectoryEntry layout:
    // 2 bytes: tag id
    // 2 bytes: data format
    // 4 bytes: number of components
    // 4 bytes: data offset or value

    // buffer needs to be at least 12 bytes long
    if (data.size() < 12) {
        fmt::print("ERROR: DirectoryEntry data buffer is too small\n");
        std::terminate();
    }

    // get tag type
    m_tag = Tag{m_byte_order.calculate({data.begin(), 2})};
    auto current_byte = data.begin() + 2;

    // get data format
    m_format = TagDataFormat{m_byte_order.calculate({current_byte, 2})};
    current_byte += 2;

    // get number of components
    m_components = m_byte_order.calculate({current_byte, 4});
    current_byte += 4;

    // get data offset or value
    m_values.push_back(m_byte_order.calculate<uint32_t>({current_byte, 4}));

    // check if data is stored in the tag itself
    if (m_components * m_format.size() <= 4) {
        // initialize value if more than one component
        if (m_components > 1) {
            m_offset = true;
            this->initialize_value({current_byte, 4});
            m_offset = false;
        }
        if (m_tag.has_subdirectory() || m_tag.has_unknown_layout()) {
            m_offset = true;
        }
    } else {
        m_offset = true;
    }
}

void DirectoryEntry::initialize_value(std::span<std::byte> data) {
    if (m_offset && !m_tag.has_subdirectory() && !m_tag.has_unknown_layout()) {
        // check buffer size
        if (data.size() < this->data_size()) {
            fmt::print("ERROR: DirectoryEntry data buffer is too small\n");
            std::terminate();
        }

        // clear values
        m_values.clear();

        // Initialize values
        auto current_byte = data.begin();
        auto size_offset = static_cast<size_t>(m_format.size());
        switch (m_format) {
            case TagDataFormat::UNSIGNED_BYTE:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<uint8_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::ASCII_STRING:
                m_values.push_back(m_byte_order.calculate<std::string>(data));
                m_offset = false;
                break;
            case TagDataFormat::UNSIGNED_SHORT:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<uint16_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::UNSIGNED_LONG:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<uint32_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::UNSIGNED_RATIONAL:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        UnsignedRational({current_byte, size_offset}, m_byte_order));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::SIGNED_BYTE:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<int8_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::UNDEFINED:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(*current_byte);
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::SIGNED_SHORT:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<int16_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::SIGNED_LONG:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<int32_t>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::SIGNED_RATIONAL:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        SignedRational({current_byte, size_offset}, m_byte_order));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::FLOAT:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<float>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
            case TagDataFormat::DOUBLE:
                current_byte = data.begin();
                for (int i = 0; i < m_components; ++i) {
                    m_values.push_back(
                        m_byte_order.calculate<double>({current_byte, size_offset}));
                    current_byte += size_offset;
                }
                m_offset = false;
                break;
        }
    }
}

}  // namespace luxlab

namespace fmt {

format_context::iterator formatter<luxlab::DirectoryEntry>::format(
    const luxlab::DirectoryEntry &entry, format_context &ctx) const {
    std::string pad = "";
    for (int i = 0; i < m_padding; ++i) {
        pad += "|    ";
    }

    std::string str = "";
    str += "\n" + pad;
    str += fmt::format("Tag 0x{:04X} - {}", entry.tag_id(), entry.tag());
    str += "\n" + pad;
    str += fmt::format("|    Format : {} x {}", entry.components(), entry.format());
    str += "\n" + pad;
    str += fmt::format("|    Size   : {} bytes", entry.data_size());
    if (entry.has_offset()) {
        auto val = std::get<uint32_t>(entry.values()[0]);
        str += "\n" + pad;
        str += fmt::format("|    Offset : 0x{:08X}", val);
    } else {
        if (entry.format() == luxlab::TagDataFormat::ASCII_STRING) {
            str += "\n" + pad;
            str += fmt::format("|    Value  : {}", entry.values()[0]);
        } else {
            for (const auto &val : entry.values()) {
                str += "\n" + pad;
                str += fmt::format("|    Value  : {}", val);
            }
        }
    }

    return format_to(ctx.out(), "{}", str);
}

}  // namespace fmt
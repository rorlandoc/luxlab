#ifndef LUXLAB_READER_HPP
#define LUXLAB_READER_HPP

#include <cstddef>
#include <filesystem>
#include <vector>

#include <fmt/core.h>
#include <nlohmann/json.hpp>

#include "luxlab/ifd.hpp"
#include "luxlab/tiff_header.hpp"

namespace luxlab {

class Reader {
   public:
    Reader(const std::filesystem::path &file_path);

    inline const std::filesystem::path &path() const { return m_path; }
    inline const std::vector<std::byte> &data() const { return m_data; }
    inline const std::vector<IFD> &ifds() const { return m_ifds; }
    inline const TIFFHeader &header() const { return m_header; }

    inline const size_t size() const { return m_data.size(); }

    void dump_hex() const;

   private:
    std::filesystem::path m_path;
    std::vector<std::byte> m_data;
    std::vector<IFD> m_ifds;
    TIFFHeader m_header;
};

void to_json(nlohmann::json &j, const Reader &reader);

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::Reader> : formatter<std::string> {
    format_context::iterator format(const luxlab::Reader &reader,
                                    format_context &ctx) const;
};

}  // namespace fmt

#endif  // !LUXLAB_READER_HPP
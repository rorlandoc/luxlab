#ifndef LUXLAB_RAW_IMAGE_HPP
#define LUXLAB_RAW_IMAGE_HPP

#include <fmt/core.h>

#include <cstddef>
#include <filesystem>
#include <vector>

#include "luxlab/exif.hpp"
#include "luxlab/ifd.hpp"
#include "luxlab/tiff_header.hpp"

namespace luxlab {

class RawImage {
   public:
    RawImage(const std::filesystem::path &file_path);

    inline const std::filesystem::path &path() const { return m_path; }
    inline const std::vector<std::byte> &data() const { return m_data; }
    inline const std::vector<IFD> &ifds() const { return m_ifds; }
    inline const Exif &exif() const { return m_exif; }
    inline const TIFFHeader &header() const { return m_header; }

    inline const size_t size() const { return m_data.size(); }

    void dump_hex() const;

   private:
    std::filesystem::path m_path;
    std::vector<std::byte> m_data;
    std::vector<IFD> m_ifds;
    Exif m_exif;
    TIFFHeader m_header;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::RawImage> : formatter<std::string> {
    format_context::iterator format(const luxlab::RawImage &raw_image,
                                    format_context &ctx) const;
};

}  // namespace fmt

#endif  // !LUXLAB_RAW_IMAGE_HPP
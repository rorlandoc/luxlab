#include "luxlab/tag_type.hpp"

#include <fmt/format.h>

namespace fmt {

format_context::iterator formatter<luxlab::TagType>::format(const luxlab::TagType& format,
                                                            format_context& ctx) const {
    std::string str = "Unknown";

    switch (format) {
        case luxlab::TagType::IMAGE_DESCRIPTION:
            str = "Image description";
            break;
        case luxlab::TagType::MAKE:
            str = "Make";
            break;
        case luxlab::TagType::MODEL:
            str = "Model";
            break;
        case luxlab::TagType::ORIENTATION:
            str = "Orientation";
            break;
        case luxlab::TagType::X_RESOLUTION:
            str = "X resolution";
            break;
        case luxlab::TagType::Y_RESOLUTION:
            str = "Y resolution";
            break;
        case luxlab::TagType::RESOLUTION_UNIT:
            str = "Resolution unit";
            break;
        case luxlab::TagType::SOFTWARE:
            str = "Software";
            break;
        case luxlab::TagType::DATE_TIME:
            str = "Date time";
            break;
        case luxlab::TagType::WHITE_POINT:
            str = "White point";
            break;
        case luxlab::TagType::PRIMARY_CHROMATICITIES:
            str = "Primary chromaticities";
            break;
        case luxlab::TagType::Y_CB_CR_COEFFICIENTS:
            str = "YCbCr coefficients";
            break;
        case luxlab::TagType::Y_CB_CR_POSITIONING:
            str = "YCbCr positioning";
            break;
        case luxlab::TagType::REFERENCE_BLACK_WHITE:
            str = "Reference black white";
            break;
        case luxlab::TagType::COPYRIGHT:
            str = "Copyright";
            break;
        case luxlab::TagType::EXIF_OFFSET:
            str = "Exif offset";
            break;
        case luxlab::TagType::EXPOSURE_TIME:
            str = "Exposure time";
            break;
        case luxlab::TagType::F_NUMBER:
            str = "F number";
            break;
        case luxlab::TagType::EXPOSURE_PROGRAM:
            str = "Exposure program";
            break;
        case luxlab::TagType::ISO_SPEED_RATINGS:
            str = "ISO speed ratings";
            break;
        case luxlab::TagType::EXIF_VERSION:
            str = "Exif version";
            break;
        case luxlab::TagType::DATE_TIME_ORIGINAL:
            str = "Date time original";
            break;
        case luxlab::TagType::DATE_TIME_DIGITIZED:
            str = "Date time digitized";
            break;
        case luxlab::TagType::COMPONENT_CONFIGURATION:
            str = "Component configuration";
            break;
        case luxlab::TagType::COMPRESSED_BITS_PER_PIXEL:
            str = "Compressed bits per pixel";
            break;
        case luxlab::TagType::SHUTTER_SPEED_VALUE:
            str = "Shutter speed value";
            break;
        case luxlab::TagType::APERTURE_VALUE:
            str = "Aperture value";
            break;
        case luxlab::TagType::BRIGHTNESS_VALUE:
            str = "Brightness value";
            break;
        case luxlab::TagType::EXPOSURE_BIAS_VALUE:
            str = "Exposure bias value";
            break;
        case luxlab::TagType::MAX_APERTURE_VALUE:
            str = "Max aperture value";
            break;
        case luxlab::TagType::SUBJECT_DISTANCE:
            str = "Subject distance";
            break;
        case luxlab::TagType::METERING_MODE:
            str = "Metering mode";
            break;
        case luxlab::TagType::LIGHT_SOURCE:
            str = "Light source";
            break;
        case luxlab::TagType::FLASH:
            str = "Flash";
            break;
        case luxlab::TagType::FOCAL_LENGTH:
            str = "Focal length";
            break;
        case luxlab::TagType::MAKER_NOTE:
            str = "Maker note";
            break;
        case luxlab::TagType::USER_COMMENT:
            str = "User comment";
            break;
        case luxlab::TagType::FLASH_PIX_VERSION:
            str = "Flash pix version";
            break;
        case luxlab::TagType::COLOR_SPACE:
            str = "Color space";
            break;
        case luxlab::TagType::EXIF_IMAGE_WIDTH:
            str = "Exif image width";
            break;
        case luxlab::TagType::EXIF_IMAGE_HEIGHT:
            str = "Exif image height";
            break;
        case luxlab::TagType::RELATED_SOUND_FILE:
            str = "Related sound file";
            break;
        case luxlab::TagType::EXIF_INTEROPERABILITY_OFFSET:
            str = "Exif interoperability offset";
            break;
        case luxlab::TagType::FOCAL_PLANE_X_RESOLUTION:
            str = "Focal plane X resolution";
            break;
        case luxlab::TagType::FOCAL_PLANE_Y_RESOLUTION:
            str = "Focal plane Y resolution";
            break;
        case luxlab::TagType::FOCAL_PLANE_RESOLUTION_UNIT:
            str = "Focal plane resolution unit";
            break;
        case luxlab::TagType::SENSING_METHOD:
            str = "Sensing method";
            break;
        case luxlab::TagType::FILE_SOURCE:
            str = "File source";
            break;
        case luxlab::TagType::SCENE_TYPE:
            str = "Scene type";
            break;
        case luxlab::TagType::IMAGE_WIDTH:
            str = "Image width";
            break;
        case luxlab::TagType::IMAGE_LENGTH:
            str = "Image length";
            break;
        case luxlab::TagType::BITS_PER_SAMPLE:
            str = "Bits per sample";
            break;
        case luxlab::TagType::COMPRESSION:
            str = "Compression";
            break;
        case luxlab::TagType::PHOTOMETRIC_INTERPRETATION:
            str = "Photometric interpretation";
            break;
        case luxlab::TagType::STRIP_OFFSETS:
            str = "Strip offsets";
            break;
        case luxlab::TagType::SAMPLES_PER_PIXEL:
            str = "Samples per pixel";
            break;
        case luxlab::TagType::ROWS_PER_STRIP:
            str = "Rows per strip";
            break;
        case luxlab::TagType::STRIP_BYTE_COUNTS:
            str = "Strip byte counts";
            break;
        case luxlab::TagType::PLANAR_CONFIGURATION:
            str = "Planar configuration";
            break;
        case luxlab::TagType::JPEG_IF_OFFSET:
            str = "JPEG IF offset";
            break;
        case luxlab::TagType::JPEG_IF_BYTE_COUNT:
            str = "JPEG IF byte count";
            break;
        case luxlab::TagType::Y_CB_CR_SUBSAMPLING:
            str = "YCbCr subsampling";
            break;
        case luxlab::TagType::NEW_SUB_FILE_TYPE:
            str = "New sub file type";
            break;
        case luxlab::TagType::SUB_FILE_TYPE:
            str = "Sub file type";
            break;
        case luxlab::TagType::TRANSFER_FUNCTION:
            str = "Transfer function";
            break;
        case luxlab::TagType::ARTIST:
            str = "Artist";
            break;
        case luxlab::TagType::PREDICTOR:
            str = "Predictor";
            break;
        case luxlab::TagType::TILE_WIDTH:
            str = "Tile width";
            break;
        case luxlab::TagType::TILE_LENGTH:
            str = "Tile length";
            break;
        case luxlab::TagType::TILE_OFFSETS:
            str = "Tile offsets";
            break;
        case luxlab::TagType::TILE_BYTE_COUNTS:
            str = "Tile byte counts";
            break;
        case luxlab::TagType::SUB_IFDS:
            str = "Sub IFDs";
            break;
        case luxlab::TagType::JPEG_TABLES:
            str = "JPEG tables";
            break;
        case luxlab::TagType::CFA_REPEAT_PATTERN_DIM:
            str = "CFA repeat pattern dim";
            break;
        case luxlab::TagType::CFA_PATTERN:
            str = "CFA pattern";
            break;
        case luxlab::TagType::BATTERY_LEVEL:
            str = "Battery level";
            break;
        case luxlab::TagType::IPTC_NAA:
            str = "IPTC NAA";
            break;
        case luxlab::TagType::INTER_COLOR_PROFILE:
            str = "Inter color profile";
            break;
        case luxlab::TagType::SPECTRAL_SENSITIVITY:
            str = "Spectral sensitivity";
            break;
        case luxlab::TagType::GPS_INFO:
            str = "GPS info";
            break;
        case luxlab::TagType::OECF:
            str = "OECF";
            break;
        case luxlab::TagType::INTERLACE:
            str = "Interlace";
            break;
        case luxlab::TagType::TIME_ZONE_OFFSET:
            str = "Time zone offset";
            break;
        case luxlab::TagType::SELF_TIMER_MODE:
            str = "Self timer mode";
            break;
        case luxlab::TagType::FLASH_ENERGY:
            str = "Flash energy";
            break;
        case luxlab::TagType::SPATIAL_FREQUENCY_RESPONSE:
            str = "Spatial frequency response";
            break;
        case luxlab::TagType::NOISE:
            str = "Noise";
            break;
        case luxlab::TagType::IMAGE_NUMBER:
            str = "Image number";
            break;
        case luxlab::TagType::SECURITY_CLASSIFICATION:
            str = "Security classification";
            break;
        case luxlab::TagType::IMAGE_HISTORY:
            str = "Image history";
            break;
        case luxlab::TagType::SUBJECT_LOCATION:
            str = "Subject location";
            break;
        case luxlab::TagType::EXPOSURE_INDEX:
            str = "Exposure index";
            break;
        case luxlab::TagType::TIFF_EP_Standard_ID:
            str = "TIFF EP standard ID";
            break;
        case luxlab::TagType::SUB_SEC_TIME:
            str = "Sub sec time";
            break;
        case luxlab::TagType::SUB_SEC_TIME_ORIGINAL:
            str = "Sub sec time original";
            break;
        case luxlab::TagType::SUB_SEC_TIME_DIGITIZED:
            str = "Sub sec time digitized";
            break;
    }

    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt
#include "luxlab/tag.hpp"

#include <fmt/format.h>

namespace fmt {

format_context::iterator formatter<luxlab::Tag>::format(const luxlab::Tag& format,
                                                        format_context& ctx) const {
    std::string str = "Unknown";

    switch (format) {
        case luxlab::Tag::IMAGE_DESCRIPTION:
            str = "Image description";
            break;
        case luxlab::Tag::MAKE:
            str = "Make";
            break;
        case luxlab::Tag::MODEL:
            str = "Model";
            break;
        case luxlab::Tag::ORIENTATION:
            str = "Orientation";
            break;
        case luxlab::Tag::X_RESOLUTION:
            str = "X resolution";
            break;
        case luxlab::Tag::Y_RESOLUTION:
            str = "Y resolution";
            break;
        case luxlab::Tag::RESOLUTION_UNIT:
            str = "Resolution unit";
            break;
        case luxlab::Tag::SOFTWARE:
            str = "Software";
            break;
        case luxlab::Tag::DATE_TIME:
            str = "Date time";
            break;
        case luxlab::Tag::WHITE_POINT:
            str = "White point";
            break;
        case luxlab::Tag::PRIMARY_CHROMATICITIES:
            str = "Primary chromaticities";
            break;
        case luxlab::Tag::Y_CB_CR_COEFFICIENTS:
            str = "YCbCr coefficients";
            break;
        case luxlab::Tag::Y_CB_CR_POSITIONING:
            str = "YCbCr positioning";
            break;
        case luxlab::Tag::REFERENCE_BLACK_WHITE:
            str = "Reference black white";
            break;
        case luxlab::Tag::COPYRIGHT:
            str = "Copyright";
            break;
        case luxlab::Tag::EXIF_IFD:
            str = "Exif IFD";
            break;
        case luxlab::Tag::EXPOSURE_TIME:
            str = "Exposure time";
            break;
        case luxlab::Tag::F_NUMBER:
            str = "F number";
            break;
        case luxlab::Tag::EXPOSURE_PROGRAM:
            str = "Exposure program";
            break;
        case luxlab::Tag::ISO_SPEED_RATINGS:
            str = "ISO speed ratings";
            break;
        case luxlab::Tag::EXIF_VERSION:
            str = "Exif version";
            break;
        case luxlab::Tag::DATE_TIME_ORIGINAL:
            str = "Date time original";
            break;
        case luxlab::Tag::DATE_TIME_DIGITIZED:
            str = "Date time digitized";
            break;
        case luxlab::Tag::COMPONENT_CONFIGURATION:
            str = "Component configuration";
            break;
        case luxlab::Tag::COMPRESSED_BITS_PER_PIXEL:
            str = "Compressed bits per pixel";
            break;
        case luxlab::Tag::SHUTTER_SPEED_VALUE:
            str = "Shutter speed value";
            break;
        case luxlab::Tag::APERTURE_VALUE:
            str = "Aperture value";
            break;
        case luxlab::Tag::BRIGHTNESS_VALUE:
            str = "Brightness value";
            break;
        case luxlab::Tag::EXPOSURE_BIAS_VALUE:
            str = "Exposure bias value";
            break;
        case luxlab::Tag::MAX_APERTURE_VALUE:
            str = "Max aperture value";
            break;
        case luxlab::Tag::SUBJECT_DISTANCE:
            str = "Subject distance";
            break;
        case luxlab::Tag::METERING_MODE:
            str = "Metering mode";
            break;
        case luxlab::Tag::LIGHT_SOURCE:
            str = "Light source";
            break;
        case luxlab::Tag::FLASH:
            str = "Flash";
            break;
        case luxlab::Tag::FOCAL_LENGTH:
            str = "Focal length";
            break;
        case luxlab::Tag::MAKER_NOTE:
            str = "Maker note";
            break;
        case luxlab::Tag::USER_COMMENT:
            str = "User comment";
            break;
        case luxlab::Tag::FLASH_PIX_VERSION:
            str = "Flash pix version";
            break;
        case luxlab::Tag::COLOR_SPACE:
            str = "Color space";
            break;
        case luxlab::Tag::EXIF_IMAGE_WIDTH:
            str = "Exif image width";
            break;
        case luxlab::Tag::EXIF_IMAGE_HEIGHT:
            str = "Exif image height";
            break;
        case luxlab::Tag::RELATED_SOUND_FILE:
            str = "Related sound file";
            break;
        case luxlab::Tag::EXIF_INTEROPERABILITY_IFD:
            str = "Exif interoperability IFD";
            break;
        case luxlab::Tag::FOCAL_PLANE_X_RESOLUTION:
            str = "Focal plane X resolution";
            break;
        case luxlab::Tag::FOCAL_PLANE_Y_RESOLUTION:
            str = "Focal plane Y resolution";
            break;
        case luxlab::Tag::FOCAL_PLANE_RESOLUTION_UNIT:
            str = "Focal plane resolution unit";
            break;
        case luxlab::Tag::SENSING_METHOD:
            str = "Sensing method";
            break;
        case luxlab::Tag::FILE_SOURCE:
            str = "File source";
            break;
        case luxlab::Tag::SCENE_TYPE:
            str = "Scene type";
            break;
        case luxlab::Tag::IMAGE_WIDTH:
            str = "Image width";
            break;
        case luxlab::Tag::IMAGE_LENGTH:
            str = "Image length";
            break;
        case luxlab::Tag::BITS_PER_SAMPLE:
            str = "Bits per sample";
            break;
        case luxlab::Tag::COMPRESSION:
            str = "Compression";
            break;
        case luxlab::Tag::PHOTOMETRIC_INTERPRETATION:
            str = "Photometric interpretation";
            break;
        case luxlab::Tag::STRIP_OFFSETS:
            str = "Strip offsets";
            break;
        case luxlab::Tag::SAMPLES_PER_PIXEL:
            str = "Samples per pixel";
            break;
        case luxlab::Tag::ROWS_PER_STRIP:
            str = "Rows per strip";
            break;
        case luxlab::Tag::STRIP_BYTE_COUNTS:
            str = "Strip byte counts";
            break;
        case luxlab::Tag::PLANAR_CONFIGURATION:
            str = "Planar configuration";
            break;
        case luxlab::Tag::JPEG_IF_OFFSET:
            str = "JPEG IF offset";
            break;
        case luxlab::Tag::JPEG_IF_BYTE_COUNT:
            str = "JPEG IF byte count";
            break;
        case luxlab::Tag::Y_CB_CR_SUBSAMPLING:
            str = "YCbCr subsampling";
            break;
        case luxlab::Tag::NEW_SUB_FILE_TYPE:
            str = "New sub file type";
            break;
        case luxlab::Tag::SUB_FILE_TYPE:
            str = "Sub file type";
            break;
        case luxlab::Tag::TRANSFER_FUNCTION:
            str = "Transfer function";
            break;
        case luxlab::Tag::ARTIST:
            str = "Artist";
            break;
        case luxlab::Tag::PREDICTOR:
            str = "Predictor";
            break;
        case luxlab::Tag::TILE_WIDTH:
            str = "Tile width";
            break;
        case luxlab::Tag::TILE_LENGTH:
            str = "Tile length";
            break;
        case luxlab::Tag::TILE_OFFSETS:
            str = "Tile offsets";
            break;
        case luxlab::Tag::TILE_BYTE_COUNTS:
            str = "Tile byte counts";
            break;
        case luxlab::Tag::SUB_IFDS:
            str = "Sub IFDs";
            break;
        case luxlab::Tag::JPEG_TABLES:
            str = "JPEG tables";
            break;
        case luxlab::Tag::CFA_REPEAT_PATTERN_DIM:
            str = "CFA repeat pattern dim";
            break;
        case luxlab::Tag::CFA_PATTERN:
            str = "CFA pattern";
            break;
        case luxlab::Tag::BATTERY_LEVEL:
            str = "Battery level";
            break;
        case luxlab::Tag::IPTC_NAA:
            str = "IPTC NAA";
            break;
        case luxlab::Tag::INTER_COLOR_PROFILE:
            str = "Inter color profile";
            break;
        case luxlab::Tag::SPECTRAL_SENSITIVITY:
            str = "Spectral sensitivity";
            break;
        case luxlab::Tag::GPS_INFO:
            str = "GPS info";
            break;
        case luxlab::Tag::OECF:
            str = "OECF";
            break;
        case luxlab::Tag::INTERLACE:
            str = "Interlace";
            break;
        case luxlab::Tag::TIME_ZONE_OFFSET:
            str = "Time zone offset";
            break;
        case luxlab::Tag::SELF_TIMER_MODE:
            str = "Self timer mode";
            break;
        case luxlab::Tag::FLASH_ENERGY:
            str = "Flash energy";
            break;
        case luxlab::Tag::SPATIAL_FREQUENCY_RESPONSE:
            str = "Spatial frequency response";
            break;
        case luxlab::Tag::NOISE:
            str = "Noise";
            break;
        case luxlab::Tag::IMAGE_NUMBER:
            str = "Image number";
            break;
        case luxlab::Tag::SECURITY_CLASSIFICATION:
            str = "Security classification";
            break;
        case luxlab::Tag::IMAGE_HISTORY:
            str = "Image history";
            break;
        case luxlab::Tag::SUBJECT_LOCATION:
            str = "Subject location";
            break;
        case luxlab::Tag::EXPOSURE_INDEX:
            str = "Exposure index";
            break;
        case luxlab::Tag::TIFF_EP_Standard_ID:
            str = "TIFF EP standard ID";
            break;
        case luxlab::Tag::SUB_SEC_TIME:
            str = "Sub sec time";
            break;
        case luxlab::Tag::SUB_SEC_TIME_ORIGINAL:
            str = "Sub sec time original";
            break;
        case luxlab::Tag::SUB_SEC_TIME_DIGITIZED:
            str = "Sub sec time digitized";
            break;
        case luxlab::Tag::XMP:
            str = "XMP";
            break;
        case luxlab::Tag::PRINT_IMAGE_MATCHING:
            str = "Print image matching";
            break;
        case luxlab::Tag::DNG_PRIVATE_DATA:
            str = "DNG private data";
            break;
        case luxlab::Tag::SONY_RAW_FILE_TYPE:
            str = "Sony raw file type";
            break;
        case luxlab::Tag::SONY_TONE_CURVE:
            str = "Sony tone curve";
            break;
        case luxlab::Tag::VIGNETTING_CORRECTION:
            str = "Vignetting correction";
            break;
        case luxlab::Tag::VIGNETTING_CORRECTION_PARAMS:
            str = "Vignetting correction params";
            break;
        case luxlab::Tag::CHROMATIC_ABERRATION_CORRECTION:
            str = "Chromatic aberration correction";
            break;
        case luxlab::Tag::CHROMATIC_ABERRATION_CORRECTION_PARAMS:
            str = "Chromatic aberration correction params";
            break;
        case luxlab::Tag::DISTORTION_CORRECTION:
            str = "Distortion correction";
            break;
        case luxlab::Tag::DISTORTION_CORRECTION_PARAMS:
            str = "Distortion correction params";
            break;
        case luxlab::Tag::BLACK_LEVEL:
            str = "Black level";
            break;
        case luxlab::Tag::WB_RGGB_LEVELS:
            str = "WB RGGB levels";
            break;
        case luxlab::Tag::SONY_CROP_TOP_LEFT:
            str = "Sony crop top left";
            break;
        case luxlab::Tag::SONY_CROP_SIZE:
            str = "Sony crop size";
            break;
        case luxlab::Tag::WHITE_LEVEL:
            str = "White level";
            break;
        case luxlab::Tag::DEFAULT_CROP_ORIGIN:
            str = "Default crop origin";
            break;
        case luxlab::Tag::DEFAULT_CROP_SIZE:
            str = "Default crop size";
            break;
    }

    return formatter<std::string>::format(str, ctx);
}

}  // namespace fmt
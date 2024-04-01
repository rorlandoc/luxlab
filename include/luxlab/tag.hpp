#ifndef LUXLAB_TAG_HPP
#define LUXLAB_TAG_HPP

#include <fmt/core.h>

namespace luxlab {

class Tag {
   public:
    enum Type : int {
        IMAGE_DESCRIPTION = 0x010e,
        MAKE = 0x010f,
        MODEL = 0x0110,
        ORIENTATION = 0x0112,
        X_RESOLUTION = 0x011a,
        Y_RESOLUTION = 0x011b,
        RESOLUTION_UNIT = 0x0128,
        SOFTWARE = 0x0131,
        DATE_TIME = 0x0132,
        WHITE_POINT = 0x013e,
        PRIMARY_CHROMATICITIES = 0x013f,
        Y_CB_CR_COEFFICIENTS = 0x0211,
        Y_CB_CR_POSITIONING = 0x0213,
        REFERENCE_BLACK_WHITE = 0x0214,
        COPYRIGHT = 0x8298,
        EXIF_IFD = 0x8769,
        EXPOSURE_TIME = 0x829a,
        F_NUMBER = 0x829d,
        EXPOSURE_PROGRAM = 0x8822,
        ISO_SPEED_RATINGS = 0x8827,
        EXIF_VERSION = 0x9000,
        DATE_TIME_ORIGINAL = 0x9003,
        DATE_TIME_DIGITIZED = 0x9004,
        COMPONENT_CONFIGURATION = 0x9101,
        COMPRESSED_BITS_PER_PIXEL = 0x9102,
        SHUTTER_SPEED_VALUE = 0x9201,
        APERTURE_VALUE = 0x9202,
        BRIGHTNESS_VALUE = 0x9203,
        EXPOSURE_BIAS_VALUE = 0x9204,
        MAX_APERTURE_VALUE = 0x9205,
        SUBJECT_DISTANCE = 0x9206,
        METERING_MODE = 0x9207,
        LIGHT_SOURCE = 0x9208,
        FLASH = 0x9209,
        FOCAL_LENGTH = 0x920a,
        MAKER_NOTE = 0x927c,
        USER_COMMENT = 0x9286,
        FLASH_PIX_VERSION = 0xa000,
        COLOR_SPACE = 0xa001,
        EXIF_IMAGE_WIDTH = 0xa002,
        EXIF_IMAGE_HEIGHT = 0xa003,
        RELATED_SOUND_FILE = 0xa004,
        EXIF_INTEROPERABILITY_IFD = 0xa005,
        FOCAL_PLANE_X_RESOLUTION = 0xa20e,
        FOCAL_PLANE_Y_RESOLUTION = 0xa20f,
        FOCAL_PLANE_RESOLUTION_UNIT = 0xa210,
        SENSING_METHOD = 0xa217,
        FILE_SOURCE = 0xa300,
        SCENE_TYPE = 0xa301,
        IMAGE_WIDTH = 0x0100,
        IMAGE_LENGTH = 0x0101,
        BITS_PER_SAMPLE = 0x0102,
        COMPRESSION = 0x0103,
        PHOTOMETRIC_INTERPRETATION = 0x0106,
        STRIP_OFFSETS = 0x0111,
        SAMPLES_PER_PIXEL = 0x0115,
        ROWS_PER_STRIP = 0x0116,
        STRIP_BYTE_COUNTS = 0x0117,
        PLANAR_CONFIGURATION = 0x011c,
        JPEG_IF_OFFSET = 0x0201,
        JPEG_IF_BYTE_COUNT = 0x0202,
        Y_CB_CR_SUBSAMPLING = 0x0212,
        NEW_SUB_FILE_TYPE = 0x00fe,
        SUB_FILE_TYPE = 0x00ff,
        TRANSFER_FUNCTION = 0x012d,
        ARTIST = 0x013b,
        PREDICTOR = 0x013d,
        TILE_WIDTH = 0x0142,
        TILE_LENGTH = 0x0143,
        TILE_OFFSETS = 0x0144,
        TILE_BYTE_COUNTS = 0x0145,
        SUB_IFDS = 0x014a,
        JPEG_TABLES = 0x015b,
        CFA_REPEAT_PATTERN_DIM = 0x828d,
        CFA_PATTERN = 0x828e,
        BATTERY_LEVEL = 0x828f,
        IPTC_NAA = 0x83bb,
        INTER_COLOR_PROFILE = 0x8773,
        SPECTRAL_SENSITIVITY = 0x8824,
        GPS_INFO = 0x8825,
        OECF = 0x8828,
        INTERLACE = 0x8829,
        TIME_ZONE_OFFSET = 0x882a,
        SELF_TIMER_MODE = 0x882b,
        FLASH_ENERGY = 0x920b,
        SPATIAL_FREQUENCY_RESPONSE = 0x920c,
        NOISE = 0x920d,
        IMAGE_NUMBER = 0x9211,
        SECURITY_CLASSIFICATION = 0x9212,
        IMAGE_HISTORY = 0x9213,
        SUBJECT_LOCATION = 0x9214,
        EXPOSURE_INDEX = 0x9215,
        TIFF_EP_Standard_ID = 0x9216,
        SUB_SEC_TIME = 0x9290,
        SUB_SEC_TIME_ORIGINAL = 0x9291,
        SUB_SEC_TIME_DIGITIZED = 0x9292,
        XMP = 0x02bc,
        PRINT_IMAGE_MATCHING = 0xc4a5,
        DNG_PRIVATE_DATA = 0xc634,

        // Sony tags
        SONY_RAW_FILE_TYPE = 0x7000,
        SONY_TONE_CURVE = 0x7010,
        VIGNETTING_CORRECTION = 0x7031,
        VIGNETTING_CORRECTION_PARAMS = 0x7032,
        CHROMATIC_ABERRATION_CORRECTION = 0x7034,
        CHROMATIC_ABERRATION_CORRECTION_PARAMS = 0x7035,
        DISTORTION_CORRECTION = 0x7036,
        DISTORTION_CORRECTION_PARAMS = 0x7037,
        BLACK_LEVEL = 0x7310,
        WB_RGGB_LEVELS = 0x7313,
        SONY_CROP_TOP_LEFT = 0x74c7,
        SONY_CROP_SIZE = 0x74c8,

        WHITE_LEVEL = 0xc61d,
        DEFAULT_CROP_ORIGIN = 0xc61f,
        DEFAULT_CROP_SIZE = 0xc620,
    };

    Tag() = default;
    constexpr Tag(Type type) : m_type(type) {}
    constexpr explicit Tag(int type) : m_type(static_cast<Type>(type)) {}

    constexpr operator Type() const { return m_type; }
    explicit operator bool() = delete;

    constexpr int id() const { return static_cast<int>(m_type); }

    constexpr bool has_subdirectory() const {
        return m_type == SUB_IFDS || m_type == EXIF_IFD || m_type == JPEG_IF_OFFSET ||
               m_type == GPS_INFO || m_type == EXIF_INTEROPERABILITY_IFD || m_type == XMP;
    }

    constexpr bool has_unknown_layout() const { return m_type == PRINT_IMAGE_MATCHING; }

   private:
    Type m_type;
};

}  // namespace luxlab

namespace fmt {

template <>
struct formatter<luxlab::Tag> : formatter<std::string> {
    format_context::iterator format(const luxlab::Tag& type, format_context& ctx) const;
};

}  // namespace fmt

#endif  // ! LUXLAB_TAG_HPP

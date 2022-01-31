#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/upfloat8low.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"

namespace pfloat_n {

    const struct pfloat8_4ranges_helper_struct upfloat8low_helper = {
            0x00, 0x01, 0x02,
            0xFF, 0xBF, 0x7F, 0x3F,
            // range related
            0xC0, 0x80, 0x40, 0x00,
            127, 126, 124, 120, 112,
            17,18,19,20,
            0x00010000, 0x0001FFFF,
            0x00020000, 0x0003FFFF,
            0x00040000, 0x0007FFFF,
            0x00080000, 0x000FFFFF,
            0x00100000, 0x001FFFFF,
            false
    };


    upfloat8low floatTOupfloat8low(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOupfloat8low_t(fp32, rounding_method) ;
    }
    upfloat8low floatTOupfloat8l(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOupfloat8low_t(fp32, rounding_method) ;
    }


    upfloat8low_t floatTOupfloat8low_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x00;
        }
        return float2pfloat8_4ranges_helper(fp32, upfloat8low_helper, rounding_method);
    }

} // end namespace pfloat_n
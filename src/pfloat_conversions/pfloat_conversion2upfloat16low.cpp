#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/upfloat16low.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"

namespace pfloat_n {

    const struct pfloat16_4ranges_helper_struct upfloat16low_t_helper = {
            0x0000, 0x0001, 0x0002,
            0xFFFF, 0xBFFF, 0x7FFF, 0x3FFF,
            // range related
            0xC000, 0x8000, 0x4000, 0x0000,
            127, 125, 121, 113, 97,
            10,11,12,13,
            0x00000200, 0x000003FF,
            0x00000400, 0x000007FF,
            0x00000800, 0x00000FFF,
            0x00001000, 0x00001FFF,
            0x00002000, 0x00003FFF,
            true
    };


    upfloat16low floatTOupfloat16low(float fp32, pfloatRoundingMethod_enum rounding_method) {
        upfloat16low temp;
        temp.set(floatTOupfloat16low_t(fp32, rounding_method));
        return temp;
    }
    upfloat16low floatTOupfloat16l(float fp32, pfloatRoundingMethod_enum rounding_method) {
        upfloat16low temp;
        temp.set(floatTOupfloat16low_t(fp32, rounding_method));
        return temp;
    }


    inline upfloat16low_t floatTOupfloat16low_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x0000;
        }
        return float2pfloat16_4ranges_helper(fp32, upfloat16low_t_helper, rounding_method);
    }

} // end namespace pfloat_n
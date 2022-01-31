#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/upfloat16high.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"


namespace pfloat_n {

    const struct pfloat16_4ranges_helper_struct upfloat16high_t_helper = {
            0x0000, 0x0001, 0x0002,
            0xFFFF, 0xBFFF, 0x7FFF, 0x3FFF,
            // range related
            0xC000, 0x8000, 0x4000, 0x0000,
            127, 123, 115, 99, 67,
            11,12,13,14,
            0x00000400, 0x000007FF,
            0x00000800, 0x00000FFF,
            0x00001000, 0x00001FFF,
            0x00002000, 0x00003FFF,
            0x00004000, 0x00007FFF,
            false
    };


    upfloat16high floatTOupfloat16high(float fp32, pfloatRoundingMethod_enum rounding_method) {
        upfloat16high temp;
        temp.set(floatTOupfloat16high_t(fp32, rounding_method));
        return temp;
    }
    upfloat16high floatTOupfloat16h(float fp32, pfloatRoundingMethod_enum rounding_method) {
        upfloat16high temp;
        temp.set(floatTOupfloat16high_t(fp32, rounding_method));
        return temp;
    }


    inline upfloat16high_t floatTOupfloat16high_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x0000;
        }
        return float2pfloat16_4ranges_helper(fp32, upfloat16high_t_helper, rounding_method);
    }

} // end namespace pfloat_n
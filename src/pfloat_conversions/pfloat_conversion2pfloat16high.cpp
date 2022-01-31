#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat16high.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"


namespace pfloat_n {

    const struct pfloat16_4ranges_helper_struct pfloat16high_t_helper = {
            0x0000, 0x0001, 0x0002,
            0x7FFF, 0x5FFF, 0x3FFF, 0x1FFF,
            // range related
            0x6000, 0x4000, 0x2000, 0x0000,
            127, 123, 115, 99, 67,
            12,13,14,15,
            0x00000800, 0x00000FFF,
            0x00001000, 0x00001FFF,
            0x00002000, 0x00003FFF,
            0x00004000, 0x00007FFF,
            0x00008000, 0x0000FFFF,
            true
    };


    pfloat16high floatTOpfloat16high(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat16high temp;
        temp.set(floatTOpfloat16high_t(fp32, rounding_method));
        return temp;
    }
    pfloat16high floatTOpfloat16h(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat16high temp;
        temp.set(floatTOpfloat16high_t(fp32, rounding_method));
        return temp;
    }

    inline pfloat16high_t floatTOpfloat16high_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat16_4ranges_helper(fp32, pfloat16high_t_helper, rounding_method);
    }
    inline pfloat16high_t floatTOpfloat16h_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat16_4ranges_helper(fp32, pfloat16high_t_helper, rounding_method);
    }

} // end namespace pfloat_n
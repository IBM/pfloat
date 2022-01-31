#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat16low.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"


namespace pfloat_n {

    const struct pfloat16_4ranges_helper_struct pfloat16low_t_helper = {
            0x0000, 0x0001, 0x0002,
            0x7FFF, 0x5FFF, 0x3FFF, 0x1FFF,
            // range related
            0x6000, 0x4000, 0x2000, 0x0000,
            127, 125, 121, 113, 97,
            11,12,13,14,
            0x00000400, 0x000007FF,
            0x00000800, 0x00000FFF,
            0x00001000, 0x00001FFF,
            0x00002000, 0x00003FFF,
            0x00004000, 0x00007FFF,
            true
    };


    pfloat16low floatTOpfloat16low(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat16low temp;
        temp.set(floatTOpfloat16low_t(fp32, rounding_method));
        return temp;
    }
    pfloat16low floatTOpfloat16l(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat16low temp;
        temp.set(floatTOpfloat16low_t(fp32, rounding_method));
        return temp;
    }


    inline pfloat16low_t floatTOpfloat16low_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat16_4ranges_helper(fp32, pfloat16low_t_helper, rounding_method);
    }

} // end namespace pfloat_n
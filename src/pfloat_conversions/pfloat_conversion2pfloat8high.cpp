#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat8high.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"


namespace pfloat_n {

    const struct pfloat8_4ranges_helper_struct pfloat8high_t_helper = {
            0x00, 0x01, 0x02,
            0x7F, 0x5F, 0x3F, 0x1F,
            // range related
            0x60, 0x40, 0x20, 0x00,
            127, 125, 121, 113, 97,
            19,20,21,22,
            0x00040000, 0x0007FFFF,
            0x00080000, 0x000FFFFF,
            0x00100000, 0x001FFFFF,
            0x00200000, 0x003FFFFF,
            0x00400000, 0x007FFFFF,
            true
    };


    pfloat8high floatTOpfloat8(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOpfloat8_t(fp32, rounding_method) ;
    }
    pfloat8high floatTOpfloat8high(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOpfloat8_t(fp32, rounding_method) ;
    }
    pfloat8high floatTOpfloat8h(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOpfloat8_t(fp32, rounding_method) ;
    }


    pfloat8high_t floatTOpfloat8_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat8_4ranges_helper(fp32, pfloat8high_t_helper, rounding_method);
    }
    pfloat8high_t floatTOpfloat8h_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat8_4ranges_helper(fp32, pfloat8high_t_helper, rounding_method);
    }
    pfloat8high_t floatTOpfloat8high_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return float2pfloat8_4ranges_helper(fp32, pfloat8high_t_helper, rounding_method);
    }

} // end namespace pfloat_n
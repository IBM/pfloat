#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/upfloat8high.h"
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"


namespace pfloat_n {

    const struct pfloat8_4ranges_helper_struct upfloat8high_helper = {
            0x00, 0x01, 0x02,
            0xFF, 0xBF, 0x7F, 0x3F,
            // range related
            0xC0, 0x80, 0x40, 0x00,
            127, 125, 121, 113, 97,
            18,19,20,21,
            0x00020000, 0x0003FFFF,
            0x00040000, 0x0007FFFF,
            0x00080000, 0x000FFFFF,
            0x00100000, 0x001FFFFF,
            0x00200000, 0x003FFFFF,
            false
    };


    upfloat8high floatTOupfloat8(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOupfloat8_t(fp32, rounding_method) ;
    }
    upfloat8high floatTOupfloat8h(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOupfloat8_t(fp32, rounding_method) ;
    }
    upfloat8high floatTOupfloat8high(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return floatTOupfloat8_t(fp32, rounding_method) ;
    }


    upfloat8high_t floatTOupfloat8_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x00;
        }
        return float2pfloat8_4ranges_helper(fp32, upfloat8high_helper, rounding_method);
    }
    upfloat8high_t floatTOupfloat8h_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x00;
        }
        return float2pfloat8_4ranges_helper(fp32, upfloat8high_helper, rounding_method);
    }
    upfloat8high_t floatTOupfloat8high_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        if (fp32 <= 0.0) { // negative numbers are mapped to zero for unsigned return type
            return 0x00;
        }
        return float2pfloat8_4ranges_helper(fp32, upfloat8high_helper, rounding_method);
    }

} // end namespace pfloat_n
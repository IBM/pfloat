#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_types/pfloat32.h"

namespace pfloat_n {

    pfloat32 floatTOpfloat32(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat32 temp;
        temp.set(floatTOpfloat32_t(fp32, rounding_method));
        return temp;
    }
    pfloat32 floatTOpfloat32(double fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat32 temp;
        temp.set(floatTOpfloat32_t(fp32, rounding_method));
        return temp;
    }

    pfloat32_t floatTOpfloat32_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        // TODO: Implement
        return 0x0000;
    }
    pfloat32_t floatTOpfloat32_t(double fp32, pfloatRoundingMethod_enum rounding_method) {
        // TODO: Implement
        return 0x0000;
    }

    } // end namespace pfloat_n
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_types/pfloat.h"


namespace pfloat_n {

    pfloat floatTOpfloat(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat temp;
        temp.set(floatTOpfloat_t(fp32, rounding_method));
        return temp;
    }
    pfloat_t floatTOpfloat_t(float fp32, pfloatRoundingMethod_enum rounding_method) {
        return fp32;
    }

} // end namespace pfloat_n

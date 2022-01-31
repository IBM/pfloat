#ifndef PFLOAT_PFLOAT_CONVERSIONHELPER_16RANGES_H
#define PFLOAT_PFLOAT_CONVERSIONHELPER_16RANGES_H

#include "pfloat_types/pfloat_types_common.h"

namespace pfloat_n {

    struct pfloat_16ranges_helper_struct {
        uint16_t zero, one, smallest;
        uint16_t rangeLargest[16];
        uint16_t rangeBits[16];
        uint32_t rangeOverflowExponent;
        uint32_t rangeExponent[16];
        int rangeExponentShift[16];
        uint32_t rangeLSBminus1[16];
        uint32_t rangeLSBminus1allBits[16];
        uint32_t underflowLSBminus1, underflowLSBminus1allBits;
        bool isSigned;
    };


    uint16_t floatTOpfloat16_helper(float fp32,
                                  const pfloat_16ranges_helper_struct helper,
                                  pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

} // end namespace pfloat_n



#endif //PFLOAT_PFLOAT_CONVERSIONHELPER_16RANGES_H

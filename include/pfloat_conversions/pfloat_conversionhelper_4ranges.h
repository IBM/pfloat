#ifndef PFLOAT_PFLOAT_CONVERSIONHELPER_4RANGES_H
#define PFLOAT_PFLOAT_CONVERSIONHELPER_4RANGES_H

#include "pfloat_types/pfloat_types_common.h"

namespace pfloat_n {

    struct pfloat8_4ranges_helper_struct {
        uint8_t zero, one, smallest;
        uint8_t range11largest, range10largest, range01largest, range00largest;
        uint8_t range11bits, range10bits, range01bits, range00bits;
        uint32_t rangeOverflowExponent, range11Exponent, range10Exponent, range01Exponent, range00Exponent;
        int range11ExponentShift, range10ExponentShift, range01ExponentShift, range00ExponentShift;
        uint32_t range11LSBminus1, range11LSBminus1allBits;
        uint32_t range10LSBminus1, range10LSBminus1allBits;
        uint32_t range01LSBminus1, range01LSBminus1allBits;
        uint32_t range00LSBminus1, range00LSBminus1allBits;
        uint32_t underflowLSBminus1, underflowLSBminus1allBits;
        bool isSigned;
    };

    struct pfloat16_4ranges_helper_struct {
        uint16_t zero, one, smallest;
        uint16_t range11largest, range10largest, range01largest, range00largest;
        uint16_t range11bits, range10bits, range01bits, range00bits;
        uint32_t rangeOverflowExponent, range11Exponent, range10Exponent, range01Exponent, range00Exponent;
        int range11ExponentShift, range10ExponentShift, range01ExponentShift, range00ExponentShift;
        uint32_t range11LSBminus1, range11LSBminus1allBits;
        uint32_t range10LSBminus1, range10LSBminus1allBits;
        uint32_t range01LSBminus1, range01LSBminus1allBits;
        uint32_t range00LSBminus1, range00LSBminus1allBits;
        uint32_t underflowLSBminus1, underflowLSBminus1allBits;
        bool isSigned;
    };



    uint8_t float2pfloat8_4ranges_helper(float fp32,
                                  const pfloat8_4ranges_helper_struct helper,
                                  pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    uint16_t float2pfloat16_4ranges_helper(float fp32,
                                         const pfloat16_4ranges_helper_struct helper,
                                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

} // end namespace pfloat_n


#endif //PFLOAT_PFLOAT_CONVERSIONHELPER_4RANGES_H

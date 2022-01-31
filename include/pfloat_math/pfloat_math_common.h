#ifndef PFLOAT_PFLOAT_MATH_COMMON_H
#define PFLOAT_PFLOAT_MATH_COMMON_H

#include <type_traits>

#include "pfloat_types/pfloat_types.h"

namespace pfloat_n {

    // Note: The FP32MantissaMask can be used to mimic a smaller mantissa than 23 bts
    // For example, a mask 0xFFFF8000 would truncate the 15 LSBs and hence limit the FP32 mantissa to just 8 bits
    // 0xFFF80000 --> 4 mantissa bits; 0xFFFF8000 --> 8 Mantissa bits;
    // 0xFFFFE000 --> 10 mantissa bits; 0xFFFFF800 --> 12 mantissa bits;
    // 0xFFFFFF80 --> 16 mantissa bits; 0xFFFFFFFF --> 23 mantissa bits
    // There must be at least 4 mantissa bits (0xFFF80000)
    // Remark: Hard truncating of mantissa bits, no rounding applied here (read: rounding only in type conversions)
    float truncateMantissa(float input, uint32_t FP32MantissaMask);

} // end namespace pfloat_n

#endif //PFLOAT_PFLOAT_MATH_COMMON_H

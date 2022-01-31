#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    float truncateMantissa(const float input, const uint32_t FP32MantissaMask) {
        // truncate the bits
        uint32_t truncated = *(uint32_t *)&input;
        truncated &= FP32MantissaMask;
        float result = *(float *)&truncated;
        return result;
    }

} // end namespace pfloat_n

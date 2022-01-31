#include "pfloat_conversions/pfloat_conversionhelper_16ranges.h"


# define pfloat16_else_if_helper(N) \
else if (exponent >= helper.rangeExponent[N]) { \
    result = helper.rangeBits[N] | \
             ((magnitudebits - (helper.rangeExponent[N] << 23)) >> helper.rangeExponentShift[N]); \
    switch (rounding_method) { \
        case nearest: \
            if (bits & helper.rangeLSBminus1[N]) {  \
                if (result == helper.rangeLargest[N]) { \
                    result = helper.rangeBits[N-1];  \
                } else { \
                result += 0x01; \
                } \
            } \
            break; \
        case up: \
            if (bits & helper.rangeLSBminus1allBits[N]) { \
                if (result == helper.rangeLargest[N]) { \
                    result = helper.rangeBits[N-1]; \
               } else { \
                   result += 0x01; \
                } \
            } \
            break; \
        case random:; \
            break; \
        case down:; \
            break; \
        default:; \
    } \
}

namespace pfloat_n {


    uint16_t floatTOpfloat16_helper(float fp32,
                                  const pfloat_16ranges_helper_struct helper,
                                  pfloatRoundingMethod_enum rounding_method) {

        uint8_t result;
        uint32_t bits = *(uint32_t *) &fp32;
        uint32_t magnitudebits = bits & 0x7FFFFFFFu;
        uint32_t exponent = (bits & 0x7f800000) >> 23;

        if (exponent >= helper.rangeOverflowExponent) {
            // overflow, we limit to magnitude of one (note that we handled 1.0 already above)
            result = helper.one;
        } else if (exponent >= helper.rangeExponent[0]) { // range bits must be 0b11 (--> 96 = 0b 0 11 0 0000)
            result = helper.rangeBits[0] |
                     ((magnitudebits - (helper.rangeExponent[0] << 23)) >> helper.rangeExponentShift[0]);
            switch (rounding_method) {
                case nearest:
                    if (bits & helper.rangeLSBminus1[0]) { // check the bit at LSB-1
                        // handle special case nearest to magnitude 1
                        if (result == helper.rangeLargest[0]) {
                            result = helper.one; // we round to 1
                        } else {
                            result += 0x01; // we round up
                        }
                    }
                    break;
                case up:
                    if (bits & helper.rangeLSBminus1allBits[0]) { // check all mantissa bits at and below LSB-1
                        // handle special case nearest to magnitude 1
                        if (result == helper.rangeLargest[0]) {
                            result = helper.one; // we round to 1
                        } else {
                            result += 0x01; // we round up
                        }
                    }
                    break;
                case random:;
                    break; // TODO: Implement random rounding
                case down:;
                    break; // nothing to do when truncating extra mantissa bits from the float
                default:; // never reached
            }
        }
        pfloat16_else_if_helper(1)
        pfloat16_else_if_helper(2)
        pfloat16_else_if_helper(3)
        pfloat16_else_if_helper(4)
        pfloat16_else_if_helper(5)
        pfloat16_else_if_helper(6)
        pfloat16_else_if_helper(7)
        pfloat16_else_if_helper(8)
        pfloat16_else_if_helper(9)
        pfloat16_else_if_helper(10)
        pfloat16_else_if_helper(11)
        pfloat16_else_if_helper(12)
        pfloat16_else_if_helper(13)
        pfloat16_else_if_helper(14)
        pfloat16_else_if_helper(15)
        else {
            // Handle underflow
            result = helper.zero; // assume deep underflow and speculatively assign zero magnitude
            if (exponent == (helper.rangeExponent[15] - 1)) { // handle the case at the smallest representable magnitude
                switch (rounding_method) {
                    case nearest:
                        if (bits & helper.underflowLSBminus1)  // check the bit at LSB-1
                            result = helper.smallest; // we round up and assign smallest representable magnitude
                        break;
                    case up:
                        if (bits & helper.underflowLSBminus1allBits)  // check all mantissa bits at and below LSB-1
                            result = helper.smallest; // we round up and assign smallest
                        break;
                    case random:
                        break; // TODO: Implement random rounding
                    case down:
                        break; // we already assigned zero magnitude, hence nothing to do here
                    default:; // never reached
                }
            }
        }

        // finally, we extract the sign bit from FP32 and set it accordingly in signed pfloat16
        if (helper.isSigned)
            result |= (bits & 0x80000000) ? 0x8000 : 0x0000;

        // return the result
        return result;
    }

} // end namespace pfloat_n

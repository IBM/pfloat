#include "pfloat_conversions/pfloat_conversionhelper_4ranges.h"

namespace pfloat_n {

    // A helper to maintain state of a simple max length LCG random number generator
    uint32_t pfloatRoundingRandomState = 0x12345678;

    // Note: Candidate is the to-be rounded 16-bit pfloat16 (exp & mantissa), INCLUDING the range bits;
    //       When rounding up, an overflow happens if exponent and mantissa in a range are all one, at which
    //       point adding 1 will automatically result in adding 1 to the range and exponent and mantissa
    //       bits become zero (as desired)
    inline void pfloat16Rounding(uint16_t& candidate,
                                 uint32_t magnitudebits,
                                 uint32_t LSBminus1, uint32_t rangeLSBminus1allBits,
                                 pfloatRoundingMethod_enum rounding_method) {

        switch (rounding_method) {
            case random:
                if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                    break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                // if the number of set bits in our random state is even, we fall thru to 'up'
            case up:
                if (magnitudebits & rangeLSBminus1allBits)  // check all mantissa bits at and below LSB-1
                    candidate += 0x0001u; // we round up
                break;
            case nearest:
                if (magnitudebits & LSBminus1) // check the bit at LSB-1
                    candidate += 0x0001u; // we round up
                break;
            case down:;
                break; // nothing to do when truncating extra mantissa bits from the float
            case stochastic: {
                uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                 rangeLSBminus1allBits;
                if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                    if ((magnitudebits & rangeLSBminus1allBits) > limit)
                        candidate += 0x01u; // we round up (otherwise, we implicitly round down)
                } else {
                    if ((magnitudebits & rangeLSBminus1allBits) >= limit)
                        candidate += 0x01u; // we round up (otherwise, we implicitly round down)
                }
            }
                break;
            default:; // never reached
        }
    }
    // same for 8-bit rounding
    inline void pfloat8Rounding(uint8_t& candidate,
                                 uint32_t magnitudebits,
                                 uint32_t LSBminus1, uint32_t rangeLSBminus1allBits,
                                 pfloatRoundingMethod_enum rounding_method) {

        switch (rounding_method) {
            case random:
                if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                    break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                // if the number of set bits in our random state is even, we fall thru to 'up'
            case up:
                if (magnitudebits & rangeLSBminus1allBits)  // check all mantissa bits at and below LSB-1
                    candidate += 0x01u; // we round up
                break;
            case nearest:
                if (magnitudebits & LSBminus1) // check the bit at LSB-1
                    candidate += 0x01u; // we round up
                break;
            case down:;
                break; // nothing to do when truncating extra mantissa bits from the float
            case stochastic: {
                uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                 rangeLSBminus1allBits;
                if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                    if ((magnitudebits & rangeLSBminus1allBits) > limit)
                        candidate += 0x01u; // we round up (otherwise, we implicitly round down)
                } else {
                    if ((magnitudebits & rangeLSBminus1allBits) >= limit)
                        candidate += 0x01u; // we round up (otherwise, we implicitly round down)
                }
            }
                break;
            default:; // never reached
        }
    }


    uint8_t float2pfloat8_4ranges_helper(float fp32,
                                  const pfloat8_4ranges_helper_struct helper,
                                  pfloatRoundingMethod_enum rounding_method) {

        uint8_t result;
        uint32_t bits = *(uint32_t *) &fp32;
        uint32_t magnitudebits = bits & 0x7FFFFFFFu;
        uint32_t exponent = (bits & 0x7f800000) >> 23;

        if (exponent >= helper.rangeOverflowExponent) {
            // overflow, we limit to magnitude of one
            result = helper.one;
        } else if (exponent >= helper.range11Exponent) { // range bits must be 0b11 (--> 96 = 0b 0 11 0 0000)
            result = helper.range11bits |
                     ((magnitudebits - (helper.range11Exponent << 23)) >> helper.range11ExponentShift);
            if (result == helper.range11largest) // handle the case where result is just next to 1.0
                switch (rounding_method) {
                    case random:
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                            break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                        // if the number of bits==0x1 in our random state is even, we fall thru to 'up'
                    case up:
                        if (bits & helper.range11LSBminus1allBits)  // check all mantissa bits at and below LSB-1
                            result = helper.one; // we round up and assign one
                        break;
                    case nearest:
                        if (bits & helper.range11LSBminus1)  // check the bit at LSB-1
                            result = helper.one; // we round up and assign smallest representable magnitude
                        break;
                    case down:;
                        break; // nothing to do when truncating extra mantissa bits from the float
                    case stochastic: {
                        uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                         helper.range11LSBminus1allBits;
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                            if ((bits & helper.range11LSBminus1allBits) > limit)
                                result = helper.one; // we round up and assign one
                        } else {
                            if ((bits & helper.range11LSBminus1allBits) >= limit)
                                result = helper.one; // we round up and assign one
                        }
                        }
                        break;
                    default:; // never reached
                }
            else {
                pfloat8Rounding(result, magnitudebits,
                                helper.range11LSBminus1, helper.range11LSBminus1allBits,
                                rounding_method);
            }
        } else if (exponent >= helper.range10Exponent) {
            result = helper.range10bits |
                     ((magnitudebits - (helper.range10Exponent << 23)) >> helper.range10ExponentShift);
            pfloat8Rounding(result, magnitudebits,
                            helper.range10LSBminus1, helper.range10LSBminus1allBits,
                            rounding_method);
        } else if (exponent >= helper.range01Exponent) {
            result = helper.range01bits |
                     ((magnitudebits - (helper.range01Exponent << 23)) >> helper.range01ExponentShift);
            pfloat8Rounding(result, magnitudebits,
                            helper.range01LSBminus1, helper.range01LSBminus1allBits,
                            rounding_method);
        } else if (exponent >= helper.range00Exponent) {
            result = helper.range00bits |
                     ((magnitudebits - (helper.range00Exponent << 23)) >> helper.range00ExponentShift);
            pfloat8Rounding(result, magnitudebits,
                            helper.range00LSBminus1, helper.range00LSBminus1allBits,
                            rounding_method);
        } else {
            // Handle underflow
            result = helper.zero; // assume deep underflow and speculatively assign zero magnitude
            if (exponent == (helper.range00Exponent - 1)) { // handle the case at the smallest representable magnitude
                switch (rounding_method) {
                    case random:
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                            break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                        // if the number of bits==0x1 in our random state is even, we fall thru to 'up'
                    case up:
                        if (bits & helper.underflowLSBminus1allBits)  // check all mantissa bits at and below LSB-1
                            result = helper.smallest; // we round up and assign smallest
                        break;
                    case nearest:
                        if (bits & helper.underflowLSBminus1)  // check the bit at LSB-1
                            result = helper.smallest; // we round up and assign smallest representable magnitude
                        break;
                    case down:;
                        break; // nothing to do when truncating extra mantissa bits from the float
                    case stochastic: {
                        uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                         helper.range11LSBminus1allBits;
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                            if ((bits & helper.range11LSBminus1allBits) > limit)
                                result = helper.smallest; // // we round up and assign smallest
                        } else {
                            if ((bits & helper.range11LSBminus1allBits) >= limit)
                                result = helper.smallest; // // we round up and assign smallest
                        }
                    }
                        break;
                    default:; // never reached
                }
            }
        }

        // finally, we extract the sign bit from FP32 and set it accordingly in signed pfloat8
        if (helper.isSigned)
            result |= (bits & 0x80000000) ? 0x80 : 0x00;

        // return the result
        return result;
    }


    uint16_t float2pfloat16_4ranges_helper(float fp32,
                                           const pfloat16_4ranges_helper_struct helper,
                                           pfloatRoundingMethod_enum rounding_method) {

        uint16_t result;
        uint32_t bits = *(uint32_t *) &fp32;
        uint32_t magnitudebits = bits & 0x7FFFFFFFu;
        uint32_t exponent = (bits & 0x7f800000) >> 23;

        if (exponent >= helper.rangeOverflowExponent) {
            // overflow, we limit to magnitude of one (note that we handled 1.0 already above)
            result = helper.one;
        } else if (exponent >= helper.range11Exponent) { // range bits must be 0b11 (--> 96 = 0b 0 11 0 0000)
            result = helper.range11bits |
                     ((magnitudebits - (helper.range11Exponent << 23)) >> helper.range11ExponentShift);
            if (result == helper.range11largest) // handle the case where result is just next to 1.0
                switch (rounding_method) {
                    case random:
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                            break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                        // if the number of bits==0x1 in our random state is even, we fall thru to 'up'
                    case up:
                        if (bits & helper.range11LSBminus1allBits)  // check all mantissa bits at and below LSB-1
                            result = helper.one; // we round up and assign one
                        break;
                    case nearest:
                        if (bits & helper.range11LSBminus1)  // check the bit at LSB-1
                            result = helper.one; // we round up and assign smallest representable magnitude
                        break;
                    case down:;
                        break; // nothing to do when truncating extra mantissa bits from the float
                    case stochastic: {
                        uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                         helper.range11LSBminus1allBits;
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                            if ((bits & helper.range11LSBminus1allBits) > limit)
                                result = helper.one; // we round up and assign one
                        } else {
                            if ((bits & helper.range11LSBminus1allBits) >= limit)
                                result = helper.one; // we round up and assign one
                        }
                    }
                        break;
                    default:; // never reached
                }
            else {
                pfloat16Rounding(result, magnitudebits,
                                helper.range11LSBminus1, helper.range11LSBminus1allBits,
                                rounding_method);
            }
        } else if (exponent >= helper.range10Exponent) {
            result = ((magnitudebits - (helper.range10Exponent << 23)) >> helper.range10ExponentShift);
            result |= helper.range10bits;
            pfloat16Rounding(result, magnitudebits,
                            helper.range10LSBminus1, helper.range10LSBminus1allBits,
                            rounding_method);
        } else if (exponent >= helper.range01Exponent) {
            result = helper.range01bits |
                     ((magnitudebits - (helper.range01Exponent << 23)) >> helper.range01ExponentShift);
            pfloat16Rounding(result, magnitudebits,
                             helper.range01LSBminus1, helper.range01LSBminus1allBits,
                             rounding_method);
        } else if (exponent >= helper.range00Exponent) {
            result = helper.range00bits |
                     ((magnitudebits - (helper.range00Exponent << 23)) >> helper.range00ExponentShift);
            pfloat16Rounding(result, magnitudebits,
                             helper.range00LSBminus1, helper.range00LSBminus1allBits,
                             rounding_method);
        } else {
            // Handle underflow
            result = helper.zero; // assume deep underflow and speculatively assign zero magnitude
            if (exponent == (helper.range00Exponent - 1)) { // handle the case at the smallest representable magnitude
                switch (rounding_method) {
                    case random:
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001)
                            break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                        // if the number of bits==0x1 in our random state is even, we fall thru to 'up'
                    case up:
                        if (bits & helper.underflowLSBminus1allBits)  // check all mantissa bits at and below LSB-1
                            result = helper.smallest; // we round up and assign smallest
                        break;
                    case nearest:
                        if (bits & helper.underflowLSBminus1)  // check the bit at LSB-1
                            result = helper.smallest; // we round up and assign smallest representable magnitude
                        break;
                    case down:;
                        break; // nothing to do when truncating extra mantissa bits from the float
                    case stochastic: {
                        uint32_t limit = ((pfloatRoundingRandomState *= 32310901u + 1013904223u) >> 7) &
                                         helper.range11LSBminus1allBits;
                        if ((__builtin_popcount(pfloatRoundingRandomState *= 32310901u + 1013904223u)) & 0x00000001) {
                            if ((bits & helper.range11LSBminus1allBits) > limit)
                                result = helper.smallest; // we round up and assign smallest representable magnitude
                        } else {
                            if ((bits & helper.range11LSBminus1allBits) >= limit)
                                result = helper.smallest; // we round up and assign smallest representable magnitude
                        }
                    }
                        break;
                    default:; // never reached
                }
            }
        }

        // finally, we extract the sign bit from FP32 and set it accordingly in signed pfloat16
        if (helper.isSigned)
            result |= (bits & 0x80000000u) ? 0x8000u : 0x0000u;

        // return the result
        return result;
    }

} // end namespace pfloat_n


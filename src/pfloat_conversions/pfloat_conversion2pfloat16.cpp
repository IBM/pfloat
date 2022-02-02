#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_types/pfloat16.h"


namespace pfloat_n {

    // A helper to maintain state of a simple max length LCG random number generator
    uint32_t pfloat16_randomState = 0x87654321;

    // Note: Candidate is the to-be rounded 16-bit pfloat16 (exp & mantissa), INCLUDING the range bits;
    //       When rounding up, an overflow happens if exponent and mantissa in a range are all one, at which
    //       point adding 1 will automatically result in adding 1 to the range and exponent and mantissa
    //       bits become zero (as desired)
    inline void pfloat16Rounding(uint16_t& candidate,
                                 uint32_t magnitudebits,
                                 uint32_t LSBminus1, uint32_t range11LSBminus1allBits,
                                 pfloatRoundingMethod_enum rounding_method) {

        switch (rounding_method) {
            case random:
                if ((__builtin_popcount(pfloat16_randomState *= 32310901u + 1013904223u)) & 0x00000001)
                    break; // if the number of set bits in our random state is odd, we round down (=do nothing)
                    // if the number of set bits in our random state is even, we fall thru to 'up'
            case up:
                if (magnitudebits & range11LSBminus1allBits)  // check all mantissa bits at and below LSB-1
                        candidate += 0x0001u; // we round up
                break;
            case nearest:
                if (magnitudebits & LSBminus1) // check the bit at LSB-1
                        candidate += 0x0001u; // we round up
                break;
            case down:;
                break; // nothing to do when truncating extra mantissa bits from the float
            default:; // never reached
        }
    }



    pfloat16 floatTOpfloat16(float fp32, pfloatRoundingMethod_enum rounding_method) {
        pfloat16 temp;
        temp.set(floatTOpfloat16_t(fp32, rounding_method));
        return temp;
    }
    pfloat16_t floatTOpfloat16_t(float fp32, pfloatRoundingMethod_enum rounding_method) {

        uint16_t result = 0x0000u;
        uint32_t bits = *(uint32_t *) &fp32;
        uint32_t magnitudebits = bits & 0x7FFFFFFFu;
        uint16_t mantissa = (bits & 0x007FFFFFu) >> 12;
        uint16_t exponent = (bits & 0x7f800000) >> 23;

        // TODO: Consider binary search to identify the exponent range (for better performance)
        if (exponent >= 192) {
            // highest range 15
            result = (exponent - 192) << 5;
            result |= mantissa >> 6;
            result |= (15 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00020000u, 0x0003FFFFu,
                             rounding_method);
        } else if (exponent >= 160) {
            // range 14
            result = (exponent - 160) << 6;
            result |= mantissa >> 5;
            result |= (14 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00010000u, 0x0001FFFFu,
                             rounding_method);
        } else if (exponent >= 144) {
            // range 13
            result = (exponent - 144) << 7;
            result |= mantissa >> 4;
            result |= (13 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00008000u, 0x0000FFFFu,
                             rounding_method);
        } else if (exponent >= 136) {
            // range 12
            result = (exponent - 136) << 8;
            result |= mantissa >> 3;
            result |= (12 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00004000u, 0x00007FFFu,
                             rounding_method);
        } else if (exponent >= 132) {
            // range 11
            result = (exponent - 132) << 9;
            result |= mantissa >> 2;
            result |= (11 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00002000u, 0x00003FFFu,
                             rounding_method);
        } else if (exponent >= 130) {
            // range 10
            result = (exponent - 130) << 10;
            result |= mantissa >> 1;
            result |= (10 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00001000u, 0x00001FFFu,
                             rounding_method);
        } else if (exponent == 129) {
            // range 9
            //result = (exponent - 129) << 11; // commented out because (exponent -129) is equal to zero
            result |= mantissa;
            result |= (9 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00000800u, 0x00000FFFu,
                             rounding_method);
        } else if (exponent == 128) {
            // range 8
            //result = (exponent - 128) << 11;
            result |= mantissa;
            result |= (8 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00000800u, 0x00000FFFu,
                             rounding_method);
        } else if (exponent == 127) {
            // range 7
            //result = (exponent - 127) << 11;
            result |= mantissa;
            result |= (7 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00000800u, 0x00000FFFu,
                             rounding_method);
        } else if (exponent == 126) {
            // range 6
            //result = (exponent - 126) << 11;
            result |= mantissa;
            result |= (6 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00000800u, 0x00000FFFu,
                             rounding_method);
        } else if (exponent >= 124) {
            // range 5
            result = (exponent - 124) << 10;
            result |= mantissa >> 1;
            result |= (5 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00001000u, 0x00001FFFu,
                             rounding_method);
        } else if (exponent >= 120) {
            // range 4
            result = (exponent - 120) << 9;
            result |= mantissa >> 2;
            result |= (4 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00002000u, 0x00003FFFu,
                             rounding_method);
        } else if (exponent >= 112) {
            // range 3
            result = (exponent - 112) << 8;
            result |= mantissa >> 3;
            result |= (3 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00004000u, 0x00007FFFu,
                             rounding_method);
        } else if (exponent >= 96) {
            // range 2
            result = (exponent - 96) << 7;
            result |= mantissa >> 4;
            result |= (2 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00008000u, 0x0000FFFFu,
                             rounding_method);
        } else if (exponent >= 64) {
            // range 1
            result = (exponent - 64) << 6;
            result |= mantissa >> 5;
            result |= (1 << 11); // set range bits
            pfloat16Rounding(result, magnitudebits,
                             0x00010000u, 0x0001FFFFu,
                             rounding_method);
        } else if (exponent >= 0) {
            // range 0 (smallest magnitude close to zero)
            result = (exponent - 0) << 5;
            result |= mantissa >> 6;
            // result |= (0 << 11); // set range bits (commented out because implicitly zero)
            pfloat16Rounding(result, magnitudebits,
                             0x00020000u, 0x0031FFFFu,
                             rounding_method);
        }

        // Handle sign bit
        result |= (bits & 0x80000000) ? 0x8000 : 0x0000;

        // return result
        return result;
    }


} // end namespace pfloat_n
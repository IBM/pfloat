#include <limits>
#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_types/pfloat_types.h"


namespace pfloat_n {

    //---------------------------------------------------------
    // CONVERSIONS FROM PFLOAT8

    struct pfloat8_4ranges_helper_struct {
        int range00shiftup, range01shiftup, range10shiftup, range11shiftup;
        int range00bias, range01bias, range10bias, range11bias;
        uint8_t rangeMask, bitsMask;
        int isUnsigned;
    };
    pfloat8_4ranges_helper_struct pfloat8high_4RangesHelperStruct{
            22, 21, 20, 19,
            97, 113, 121, 125,
            0x60, 0x1F,
            0
    };
    pfloat8_4ranges_helper_struct pfloat8low_4RangesHelperStruct{
            21, 20, 19, 18,
            112, 120, 124, 126,
            0x60, 0x1F,
            0
    };
    pfloat8_4ranges_helper_struct upfloat8high_4RangesHelperStruct{
            21, 20, 19, 18,
            97, 113, 121, 125,
            0xC0, 0x3F,
            1
    };
    pfloat8_4ranges_helper_struct upfloat8low_4RangesHelperStruct{
            20, 19, 18, 17,
            112, 120, 124, 126,
            0xC0, 0x3F,
            1
    };

    float pfloat8TOfloat_helper(uint8_t pfloat8, pfloat8_4ranges_helper_struct helper);

    // Signed pfloat8
    float pfloat8TOfloat(pfloat8 pfloat8) {
        return pfloat8TOfloat(pfloat8.get());
    }
    float pfloat8highTOfloat(pfloat8high pfloat8) {
        return pfloat8TOfloat(pfloat8.get());
    }
    float pfloat8hTOfloat(pfloat8 pfloat8) {
        return pfloat8TOfloat(pfloat8.get());
    }
    float pfloat8TOfloat(pfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, pfloat8high_4RangesHelperStruct);
    }
    float pfloat8highTOfloat(pfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, pfloat8high_4RangesHelperStruct);
    }
    float pfloat8hTOfloat(pfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, pfloat8high_4RangesHelperStruct);
    }

    float pfloat8lowTOfloat(pfloat8low pfloat8) {
        return pfloat8lowTOfloat(pfloat8.get());
    }
    float pfloat8lowTOfloat(pfloat8low_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, pfloat8low_4RangesHelperStruct);
    }

    // unsigned pfloat8
    float upfloat8TOfloat(upfloat8 pfloat8) {
        return upfloat8TOfloat(pfloat8.get());
    }
    float upfloat8highTOfloat(upfloat8 pfloat8) {
        return upfloat8TOfloat(pfloat8.get());
    }
    float upfloat8hTOfloat(upfloat8 pfloat8) {
        return upfloat8TOfloat(pfloat8.get());
    }
    float upfloat8TOfloat(upfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, upfloat8high_4RangesHelperStruct);
    }
    float upfloat8highTOfloat(upfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, upfloat8high_4RangesHelperStruct);
    }
    float upfloat8hTOfloat(upfloat8_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, upfloat8high_4RangesHelperStruct);
    }
    float upfloat8lowTOfloat(upfloat8low pfloat8) {
        return upfloat8lowTOfloat(pfloat8.get());
    }
    float upfloat8lowTOfloat(upfloat8low_t pfloat8) {
        return pfloat8TOfloat_helper(pfloat8, upfloat8low_4RangesHelperStruct);
    }

    // Conversion from pfloat8 helper
    float pfloat8TOfloat_helper(uint8_t pfloat8, pfloat8_4ranges_helper_struct helper) {
        uint32_t result = 0x00000000u;
        switch ((pfloat8 & helper.rangeMask) >> helper.isUnsigned) { // extract range bits: 0b 0110 0000 = 0x60
            case 0: // range bits 0b00  (0b 000 0000 = 0x00 = 0)
                switch (pfloat8 & helper.bitsMask) { // extract the number bits to determine zero, one or normal number
                    case 0x00: // is zero
                        // result = 0; // implicit due to initialization of result to zero
                        break;
                    case 0x01: // is one (0b 0011 1111 1000 0000 0000 0000 0000 = 0x3f800000)
                        result = 0x3f800000u;
                        break;
                    default: // is normal number
                        result = ((pfloat8 & helper.bitsMask) << helper.range00shiftup) + (helper.range00bias << 23);
                }
                break;
            case 32: // range bits 0b01 (0b 0010 0000 = 0x20 = 32)
                result = ((pfloat8 & helper.bitsMask) << helper.range01shiftup) + (helper.range01bias << 23);
                break;
            case 64: // range bits 0b10 (0b 0100 0000 = 0x40 = 64)
                result = ((pfloat8 & helper.bitsMask) << helper.range10shiftup) + (helper.range10bias << 23);
                break;
            case 96: // range bits 0b11 (0b 0110 0000 = 0x60 = 96)
                result = ((pfloat8 & helper.bitsMask) << helper.range11shiftup) + (helper.range11bias << 23);
                break;
            default:; // never used
        }
        // for signed pfloat, extract the sign bit from pfloat8 and set it accordingly in FP32
        if (helper.isUnsigned == 0)
            result |= (pfloat8 & 0x80) ? 0x80000000u : 0x00000000u;

        return *(float *) &result; // interpret the uint32 as 32-bit floating point figure
    }

    //---------------------------------------------------------
    // CONVERSIONS FROM PFLOAT16 (4 RANGE VERSIONS)

    struct pfloat16_4ranges_helper_struct {
        int range00shiftup, range01shiftup, range10shiftup, range11shiftup;
        int range00bias, range01bias, range10bias, range11bias;
        uint16_t rangeMask, bitsMask;
        int isUnsigned;
    };
    pfloat16_4ranges_helper_struct pfloat16high_4RangesHelperStruct{
            15, 14, 13, 12,
            67, 99, 115, 123,
            0x6000, 0x1FFF,
            0
    };
    pfloat16_4ranges_helper_struct pfloat16low_4RangesHelperStruct{
            14, 13, 12, 11,
            97, 113, 121, 125,
            0x6000, 0x1FFF,
            0
    };
    pfloat16_4ranges_helper_struct upfloat16high_4RangesHelperStruct{
            14, 13, 12, 11,
            67, 99, 115, 123,
            0xC000, 0x3FFF,
            1
    };
    pfloat16_4ranges_helper_struct upfloat16low_4RangesHelperStruct{
            13, 12, 11, 10,
            97, 113, 121, 125,
            0xC000, 0x3FFF,
            1
    };

    float pfloat16TOfloat_helper(uint16_t pfloat16, pfloat16_4ranges_helper_struct helper);

    // Signed pfloat16
    float pfloat16highTOfloat(pfloat16high pfloat16) {
        return pfloat16highTOfloat(pfloat16.get());
    }
    float pfloat16highTOfloat(pfloat16high_t pfloat16) {
        return pfloat16TOfloat_helper(pfloat16, pfloat16high_4RangesHelperStruct);
    }

    float pfloat16lowTOfloat(pfloat16low pfloat16) {
        return pfloat16lowTOfloat(pfloat16.get());
    }
    float pfloat16lowTOfloat(pfloat16low_t pfloat16) {
        return pfloat16TOfloat_helper(pfloat16, pfloat16low_4RangesHelperStruct);
    }

    // unsigned pfloat16
    float upfloat16highTOfloat(upfloat16high pfloat16) {
        return upfloat16highTOfloat(pfloat16.get());
    }
    float upfloat16highTOfloat(upfloat16high_t pfloat16) {
        return pfloat16TOfloat_helper(pfloat16, upfloat16high_4RangesHelperStruct);
    }

    float upfloat16lowTOfloat(upfloat16low pfloat16) {
        return upfloat16lowTOfloat(pfloat16.get());
    }
    float upfloat16lowTOfloat(upfloat16low_t pfloat16) {
        return pfloat16TOfloat_helper(pfloat16, upfloat16low_4RangesHelperStruct);
    }

    // Conversion from pfloat16 helper
    float pfloat16TOfloat_helper(uint16_t pfloat16, pfloat16_4ranges_helper_struct helper) {
        uint32_t result = 0x00000000u;
        switch ((pfloat16 & helper.rangeMask) >> helper.isUnsigned) { // extract range bits: 0b 0110 0000 ..= 0x60000
            case 0: // range bits 0b00  (0b 000 0000 = 0x00 = 0)
                switch (pfloat16 & helper.bitsMask) { // extract the number bits to determine zero, one or normal number
                    case 0x0000u: // is zero
                        // result = 0; // implicit due to initialization of result to zero
                        break;
                    case 0x0001u: // is one (0b 0011 1111 1000 0000 0000 0000 0000 = 0x3f800000)
                        result = 0x3f800000u;
                        break;
                    default: // is normal number
                        result = ((pfloat16 & helper.bitsMask) << helper.range00shiftup) + (helper.range00bias << 23);
                }
                break;
            case 8192: // range bits 0b01 (0b 0010 0000 0000 0000 = 0x2000 = 8192)
                result = ((pfloat16 & helper.bitsMask) << helper.range01shiftup) + (helper.range01bias << 23);
                break;
            case 16384: // range bits 0b10 (0b 0100 0000 0000 0000 = 0x4000 = 16384)
                result = ((pfloat16 & helper.bitsMask) << helper.range10shiftup) + (helper.range10bias << 23);
                break;
            case 24576: // range bits 0b11 (0b 0110 0000 0000 0000 = 0x6000 = 24576)
                result = ((pfloat16 & helper.bitsMask) << helper.range11shiftup) + (helper.range11bias << 23);
                break;
            default:; // never used
        }
        // for signed pfloat, extract the sign bit from pfloat16 and set it accordingly in FP32
        if (helper.isUnsigned == 0)
            result |= (pfloat16 & 0x8000) ? 0x80000000u : 0x00000000u;

        return *(float *) &result; // interpret the uint32 as 32-bit floating point figure
    }

    //---------------------------------------------------------
    // CONVERSION FROM PFLOAT16 (16 RANGE VERSION)
    float pfloat16TOfloat(pfloat16 pfloat16) {
        return pfloat16TOfloat(pfloat16.get());
    }

    float pfloat16TOfloat(pfloat16_t pfloat16) {
        uint32_t result = 0x00000000u;
        uint32_t pfloat16l = pfloat16;
        switch ((pfloat16 & 0x7800) >>  11){ // extract range bits: 0b 0111 1000 ..= 0x7800 (and shift to right aligned)
            case 0: // range bits 0b0000 --> smallest magnitudes
                // Remark: This also (automatically) handles subnormal float numbers
                result = ((pfloat16l & 0x07FF) << 18);
                break;
            case 1:
                result = ((pfloat16l & 0x07FF) << 17) + (64 << 23);
                break;
            case 2:
                result = ((pfloat16l & 0x07FF) << 16) + (96 << 23);
                break;
            case 3:
                result = ((pfloat16l & 0x07FF) << 15) + (112 << 23);
                break;
            case 4:
                result = ((pfloat16l & 0x07FF) << 14) + (120 << 23);
                break;
            case 5:
                result = ((pfloat16l & 0x07FF) << 13) + (124 << 23);
                break;
            case 6:
                result = ((pfloat16l & 0x07FF) << 12) + (126 << 23);
                break;
            case 7:
                result = ((pfloat16l & 0x07FF) << 12) + (127 << 23);
                break;
            case 8:
                result = ((pfloat16l & 0x07FF) << 12) + (128 << 23);
                break;
            case 9:
                result = ((pfloat16l & 0x07FF) << 12) + (129 << 23);
                break;
            case 10:
                result = ((pfloat16l & 0x07FF) << 13) + (130 << 23);
                break;
            case 11:
                result = ((pfloat16l & 0x07FF) << 14) + (132 << 23);
                break;
            case 12:
                result = ((pfloat16l & 0x07FF) << 15) + (136 << 23);
                break;
            case 13:
                result = ((pfloat16l & 0x07FF) << 16) + (144 << 23);
                break;
            case 14:
                result = ((pfloat16l & 0x07FF) << 17) + (160 << 23);
                break;
            case 15: // range bits are all one --> 0b s111 1eee eeem mmmm (6 exponent bits, 5 mantissa bits)
                if ((pfloat16 & 0x07E0) == 0x07E0) // all 6 pfloat16 exponent bits are 1
                    if (pfloat16 & 0x001F)  // exponents are all one, and (some) mantissa bits are set
                        // --> return nan
                        return std::numeric_limits<float>::quiet_NaN();
                    else // exponents are all one, but all mantissa bits are zero
                        // --> assign float infinity bit pattern
                        result = 0x7F80000;
                else // not all exponent bits are 1, handle as usual
                    result = ((pfloat16 & 0x07FF) << 18) + (192 << 23);
                break;
            default:; // never used
        }
        // extract the sign bit from pfloat16 and set it accordingly in FP32
        result |= (pfloat16 & 0x8000u) ? 0x80000000u : 0x00000000u;

        return *(float *) &result; // interpret the uint32 as 32-bit floating point figure
    }

    //---------------------------------------------------------
    // CONVERSION FROM PFLOAT32 (16 RANGE VERSION)
//    float pfloat32TOfloat(pfloat16_t pfloat16);
    float pfloat32TOfloat(pfloat32 pfloat32) {
        return pfloat32TOfloat(pfloat32.get());
    }
    float pfloat32TOfloat(pfloat32_t pfloat32) {
        // TODO: Implement
        return 0.0f;
    }

    //---------------------------------------------------------
    // CONVERSION FROM PFLOAT (WRAPPER CLASS FOR FLOAT)
//    float pfloat32TOfloat(pfloat16_t pfloat16);
    float pfloatTOfloat(pfloat pfloat) {
        return pfloatTOfloat(pfloat.get());
    }
    float pfloatTOfloat(pfloat_t pfloat) {
        return pfloat;
    }


} // end namespace pfloat_n
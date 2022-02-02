#ifndef PFLOAT_PFLOAT_CONVERSIONS_COMMON_H
#define PFLOAT_PFLOAT_CONVERSIONS_COMMON_H

#include <type_traits>

#include "pfloat_types/pfloat_types_common.h"

namespace pfloat_n{

    // ---------CONVERSIONS TO pfloat8-------------------
    // Convert FP32 (aka float) to pfloat8 (aka pfloat8high) and round
    pfloat8high floatTOpfloat8(float fp32,
                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8high floatTOpfloat8h(float fp32,
                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8high floatTOpfloat8high(float fp32,
                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8high_t floatTOpfloat8_t(float fp32,
                               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8high_t floatTOpfloat8h_t(float fp32,
                               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8high_t floatTOpfloat8high_t(float fp32,
                               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat8low----------------
    // Convert FP32 (aka float) to pfloat8low and round
    pfloat8low floatTOpfloat8low(float fp32,
                                 pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat8low_t floatTOpfloat8low_t(float fp32,
                                     pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO upfloat8high----------------
    // Convert FP32 (aka float) to upfloat8 (aka upfloat8high) and round
    upfloat8high floatTOupfloat8(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8high floatTOupfloat8h(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8high floatTOupfloat8high(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8high_t floatTOupfloat8_t(float fp32,
                                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8high_t floatTOupfloat8h_t(float fp32,
                                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8high_t floatTOupfloat8high_t(float fp32,
                                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO upfloat8low----------------
    // Convert FP32 (aka float) to upfloat8low and round
    upfloat8low floatTOupfloat8low(float fp32,
                                  pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat8low_t floatTOupfloat8low_t(float fp32,
                                      pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat16high-------------------
    // Convert FP32 (aka float) to pfloat16high and round
    pfloat16high_t floatTOpfloat16high_t(float fp32,
                                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat16high floatTOpfloat16high(float fp32,
                                     pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat16low----------------
    // Convert FP32 (aka float) to pfloat16low and round
    pfloat16low floatTOpfloat16low(float fp32,
                                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat16low_t floatTOpfloat16low_t(float fp32,
                                       pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO upfloat16high----------------
    // Convert FP32 (aka float) to upfloat16high and round
    upfloat16high floatTOupfloat16high(float fp32,
                                       pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat16high_t floatTOupfloat16high_t(float fp32,
                                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO upfloat16low----------------
    // Convert FP32 (aka float) to upfloat16low and round
    upfloat16low floatTOupfloat16low(float fp32,
                                     pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    upfloat16low_t floatTOupfloat16low_t(float fp32,
                                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat16----------------
    // Convert FP32 (aka float) to pfloat16 and round
    pfloat16 floatTOpfloat16(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat16_t floatTOpfloat16_t(float fp32,
                                 pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat32----------------
    // Convert FP32 (aka float) to pfloat32 and round
    pfloat32 floatTOpfloat32(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat32_t floatTOpfloat32_t(float fp32,
                                 pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat32 floatTOpfloat32(double fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat32_t floatTOpfloat32_t(double fp32,
                                 pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO pfloat----------------
    // Convert FP32 (aka float) to pfloat
    pfloat floatTOpfloat(float fp32,
                             pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    pfloat_t floatTOpfloat_t(float fp32,
                                 pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    // ---------CONVERSIONS TO float----------------
    // Convert pfloat8 (aka pfloat8high) to FP32 (aka float)
    float pfloat8TOfloat(pfloat8_t pfloat8);
    float pfloat8TOfloat(pfloat8 pfloat8);
    float pfloat8highTOfloat(pfloat8high_t pfloat8);
    float pfloat8highTOfloat(pfloat8high pfloat8);
    float pfloat8hTOfloat(pfloat8_t pfloat8);
    float pfloat8hTOfloat(pfloat8 pfloat8);
    // Convert pfloat8low to FP32 (aka float)
    float pfloat8lowTOfloat(pfloat8low_t pfloat8);
    float pfloat8lowTOfloat(pfloat8low pfloat8);
    // Convert upfloat8 (aka upfloat8high) to FP32 (aka float)
    float upfloat8TOfloat(upfloat8high_t upfloat8);
    float upfloat8TOfloat(upfloat8high upfloat8);
    float upfloat8highTOfloat(upfloat8high_t upfloat8);
    float upfloat8highTOfloat(upfloat8high upfloat8);
    float upfloat8hTOfloat(upfloat8high_t upfloat8);
    float upfloat8hTOfloat(upfloat8high upfloat8);
    // Convert upfloat8low to FP32 (aka float)
    float upfloat8lowTOfloat(upfloat8low_t upfloat8);
    float upfloat8lowTOfloat(upfloat8low upfloat8);
    // Convert pfloat16high to FP32 (aka float)
    float pfloat16highTOfloat(pfloat16high_t pfloat16);
    float pfloat16highTOfloat(pfloat16high pfloat16);
    // Convert pfloat16low to FP32 (aka float)
    float pfloat16lowTOfloat(pfloat16low_t pfloat16);
    float pfloat16lowTOfloat(pfloat16low pfloat16);
    // Convert upfloat16high to FP32 (aka float)
    float upfloat16highTOfloat(upfloat16high_t upfloat16);
    float upfloat16highTOfloat(upfloat16high upfloat16);
    // Convert upfloat16low to FP32 (aka float)
    float upfloat16lowTOfloat(upfloat16low_t upfloat16);
    float upfloat16lowTOfloat(upfloat16low upfloat16);
    // Convert pfloat16 to FP32 (aka float)
    float pfloat16TOfloat(pfloat16_t pfloat16);
    float pfloat16TOfloat(pfloat16 pfloat16);
    // Convert pfloat32 to FP32 (aka float)
    float pfloat32TOfloat(pfloat32_t pfloat32);
    float pfloat32TOfloat(pfloat32 pfloat32);
    // Convert pfloat to FP32 (aka float)
    float pfloatTOfloat(pfloat_t pfloat);
    float pfloatTOfloat(pfloat pfloat);

    // dummy helpers
    inline float floatTOfloat(float input,
                              pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod){
        return input;
    }


    // ---------CONVERSIONS TO double----------------
    // TODO: Consider adding conversions to double

    // ---------CONVERSIONS TO/FROM bfloat16----------------
    // TODO: Consider to implement conversion from all possible types (not only from float)
    // TODO: Add random (and stochastic) rounding
    inline uint16_t floatTObfloat16(float input,
                                    pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod){
        uint32_t bits = *(uint32_t *) &input;
        uint16_t result = bits >> 16;
        switch (rounding_method) {
            case nearest: if (bits & 0x00008000u) result += 1; break;
            case up: if (bits & 0x0000FFFFu) result += 1; break;
            case random: break; // TODO: Implement random rounding
            case down: break; // nothing to do here
            default: ;
        }
        return result;
    }
    inline float bfloat16TOfloat(uint16_t input) {
        uint32_t result = input << 16;
        return *(float*)&result;
    }

} // end namespace pfloat_n


#endif //PFLOAT_PFLOAT_CONVERSIONS_COMMON_H

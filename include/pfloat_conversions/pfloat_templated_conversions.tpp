#ifndef PFLOAT_PFLOAT_TEMPLATED_CONVERSIONS_H
#define PFLOAT_PFLOAT_TEMPLATED_CONVERSIONS_H


#include "pfloat_conversions/pfloat_conversions_common.h"


namespace pfloat_n {

    // ==========================================================
    // TEMPLATE DEFINITIONS

    template<class source_t, class target_t>
    target_t pfloat2ieee(source_t input,
                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    template<class source_t>
    float pfloat2float(source_t input,
                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    template<typename source_t, class target_t>
    target_t ieee2pfloat(source_t ieee_float,
                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);
    template<class target_t>
    target_t float2pfloat(float ieee_float,
                         pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);

    template<class source_t, class target_t>
    target_t pfloat2pfloat(source_t pfloat,
                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod);


    // ==========================================================
    // TEMPLATE IMPLEMENTATIONS

    // helpers define
#define pfloat_sourceTOtarget(source, TO, target) source##TO##target
#define pfloat_createConversion(source, target) \
    template<class source_t, class target_t> \
    inline typename std::enable_if< \
            std::is_same<source_t, source>::value && \
            std::is_same<target_t, target>::value, \
            target_t>::type convert_(source_t input, \
                                     pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod) { \
        return pfloat_sourceTOtarget(source, TO, target)(input); \
    }
// Remark: For pfloat to pfloat conversions, we first convert source to float, and then from float to target
#define pfloat_createConversion_p2p(source, target) \
    template<class source_t, class target_t> \
    inline typename std::enable_if< \
            std::is_same<source_t, source>::value && \
            std::is_same<target_t, target>::value, \
            target_t>::type convert_p2p(source_t input, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod) { \
        return pfloat_sourceTOtarget(float, TO, target)( pfloat_sourceTOtarget(source, TO, float)(input) ); \
    }
#define pfloat_createAllConversions_p2p(base_t) \
           pfloat_createConversion_p2p(base_t, pfloat8high) \
           pfloat_createConversion_p2p(base_t, pfloat8low) \
           pfloat_createConversion_p2p(base_t, upfloat8high) \
           pfloat_createConversion_p2p(base_t, upfloat8low) \
           pfloat_createConversion_p2p(base_t, pfloat16high) \
           pfloat_createConversion_p2p(base_t, pfloat16low) \
           pfloat_createConversion_p2p(base_t, upfloat16high) \
           pfloat_createConversion_p2p(base_t, upfloat16low) \
           pfloat_createConversion_p2p(base_t, pfloat16) \
           pfloat_createConversion_p2p(base_t, pfloat32) \
           pfloat_createConversion_p2p(base_t, pfloat)


    // ---------CONVERSIONS pfloat -> ieee floating point format-------------------

    // TODO: Enable conversions to double
    pfloat_createConversion(pfloat8high, float)
//    pfloat_createConversion(pfloat8, double)
    pfloat_createConversion(pfloat8low, float)
//    pfloat_createConversion(pfloat8low, double)
    pfloat_createConversion(upfloat8high, float)
//    pfloat_createConversion(upfloat8, double)
    pfloat_createConversion(upfloat8low, float)
//    pfloat_createConversion(upfloat8low, double)

    pfloat_createConversion(pfloat16high, float)
    pfloat_createConversion(pfloat16low, float)
    pfloat_createConversion(upfloat16high, float)
    pfloat_createConversion(upfloat16low, float)

    pfloat_createConversion(pfloat16, float)
    pfloat_createConversion(pfloat32, float)
    pfloat_createConversion(pfloat, float)

    template<class source_t, class target_t>
    target_t pfloat2ieee(source_t input, pfloatRoundingMethod_enum rounding_method) {
        return convert_<source_t, target_t>(input, rounding_method);
    }
    template<class source_t>
    float pfloat2float(source_t input, pfloatRoundingMethod_enum rounding_method) {
        return convert_<source_t, float>(input, rounding_method);
    }

    // ---------CONVERSIONS ieee floating point format -> some pfloat type-------------------

    // TODO: Enable conversions from double

    pfloat_createConversion(float, pfloat8high)
    pfloat_createConversion(float, pfloat8low)
    pfloat_createConversion(float, upfloat8high)
    pfloat_createConversion(float, upfloat8low)

    pfloat_createConversion(float, pfloat16high)
    pfloat_createConversion(float, pfloat16low)
    pfloat_createConversion(float, upfloat16high)
    pfloat_createConversion(float, upfloat16low)

    pfloat_createConversion(float, pfloat16)
    pfloat_createConversion(float, pfloat32)
    pfloat_createConversion(float, pfloat)

    template<typename source_t, class target_t>
    target_t ieee2pfloat(source_t ieee_float, pfloatRoundingMethod_enum rounding_method) {
        return convert_<source_t, target_t>(ieee_float, rounding_method);
    }
    template<class target_t>
    target_t float2pfloat(float ieee_float, pfloatRoundingMethod_enum rounding_method) {
        return convert_<float, target_t>(ieee_float, rounding_method);
    }

    // ---------CONVERSIONS pfloat -> pfloat-------------------

    pfloat_createAllConversions_p2p(pfloat8high)
    pfloat_createAllConversions_p2p(pfloat8low)
    pfloat_createAllConversions_p2p(upfloat8high)
    pfloat_createAllConversions_p2p(upfloat8low)
    pfloat_createAllConversions_p2p(pfloat16high)
    pfloat_createAllConversions_p2p(pfloat16low)
    pfloat_createAllConversions_p2p(upfloat16high)
    pfloat_createAllConversions_p2p(upfloat16low)
    pfloat_createAllConversions_p2p(pfloat16)
    pfloat_createAllConversions_p2p(pfloat32)
    pfloat_createAllConversions_p2p(pfloat)


    template<typename source_t, class target_t>
    target_t pfloat2pfloat(source_t pfloat, pfloatRoundingMethod_enum rounding_method) {
        return convert_p2p<source_t, target_t>(pfloat, rounding_method);
    }


} // end of namespace pfloat_n

#endif  // PFLOAT_PFLOAT_TEMPLATED_CONVERSIONS_H
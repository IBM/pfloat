#ifndef PFLOAT_PFLOAT_TEMPLATED_SCALAR_MATH_H
#define PFLOAT_PFLOAT_TEMPLATED_SCALAR_MATH_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    // ==========================================================
    // TEMPLATE DEFINITIONS

    // ---------SCALAR MATH FUNCTIONS-------------------
    // A poor man's implementation of arbitrary math functions

    using unaryMathFunctionFloat_t = float (*)(float);
    using unaryMathFunctionDouble_t = double (*)(double);

    template<class output_t, class argument_t, typename mathFunction_t = unaryMathFunctionFloat_t>
    output_t pfloatMathFunction(argument_t argument, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                          uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask);

    using binaryMathFunctionFloat_t = float (*)(float, float);
    using binaryMathFunctionDouble_t = double (*)(double, double);

    template<class output_t, class argument_t, class argument2_t = argument_t, typename mathFunction_t = binaryMathFunctionFloat_t>
    output_t pfloatMathFunction(argument_t argument1, argument2_t argument2, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                          uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask);


    // ==========================================================
    // TEMPLATE IMPLEMENTATIONS

    template<class output_t, class argument_t, typename mathFunction_t>
    inline output_t mathFunctionDo(argument_t argument, mathFunction_t function,
                                           pfloatRoundingMethod_enum rounding_method,
                                           uint32_t FP32MantissaMask) {
            float argument_f = pfloat2float<argument_t>(argument);
            float temp = truncateMantissa((function)(argument_f), FP32MantissaMask);
            return float2pfloat<output_t>(temp, rounding_method);
    }

    template<class output_t, class argument1_t, class argument2_t, typename mathFunction_t>
    output_t mathFunction2Do(argument1_t argument1, argument2_t argument2, mathFunction_t function,
                                            pfloatRoundingMethod_enum rounding_method,
                                            uint32_t FP32MantissaMask) {
            float argument1_f = pfloat2float<argument1_t>(argument1);
            float argument2_f = pfloat2float<argument2_t>(argument2);
            float temp = truncateMantissa((function)(argument1_f, argument2_f), FP32MantissaMask);
            return float2pfloat<output_t>(temp, rounding_method);
    }

    // ------------------------------------------
    // Functions with one argument

    template<class output_t, class argument_t, typename mathFunction_t>
    output_t pfloatMathFunction(argument_t argument, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method,
                          uint32_t FP32MantissaMask) {
        return mathFunctionDo<output_t, argument_t, mathFunction_t>(argument, function,
                                                                    rounding_method, FP32MantissaMask);
    }

    // ------------------------------------------
    // Functions with two arguments

    template<class output_t, class argument_t, class argument2_t, typename mathFunction_t>
    output_t pfloatMathFunction(argument_t argument1, argument2_t argument2, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method,
                          uint32_t FP32MantissaMask) {
        return mathFunction2Do<output_t, argument_t, argument2_t, mathFunction_t>(argument1, argument2, function,
                                                                                  rounding_method, FP32MantissaMask);
    }

} // end namespace pfloat_n


#endif // PFLOAT_PFLOAT_TEMPLATED_SCALAR_MATH_H

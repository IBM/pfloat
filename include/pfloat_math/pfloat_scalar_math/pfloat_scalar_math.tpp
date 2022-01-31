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

    // helpers defines
#define pfloat_sourceTOtarget_scalarMath(source, TO, target) source##TO##target
#define pfloat_createSingleArgumentMathFunction(input, output) \
    template<class output_t, class argument_t, typename mathFunction_t> \
    inline typename std::enable_if< \
            std::is_same<argument_t, input>::value && \
            std::is_same<output_t, output>::value && \
            std::is_same<mathFunction_t, unaryMathFunctionFloat_t>::value, \
            output_t>::type mathFunctionDo(argument_t argument, mathFunction_t function, \
                                           pfloatRoundingMethod_enum rounding_method, \
                                           uint32_t FP32MantissaMask) {                  \
            float argument_f = pfloat_sourceTOtarget_scalarMath(input, TO, float)(argument); \
            float temp = truncateMantissa((function)(argument_f), FP32MantissaMask); \
            return pfloat_sourceTOtarget_scalarMath(float, TO, output)(temp, rounding_method); \
    }
#define pfloat_createTwoArgumentMathFunction(input1, input2, output) \
    template<class output_t, class argument1_t, class argument2_t, typename mathFunction_t> \
    inline typename std::enable_if< \
            std::is_same<output_t, output>::value && \
            std::is_same<argument1_t, input1>::value && \
            std::is_same<argument2_t, input2>::value && \
            std::is_same<output_t, output>::value && \
            std::is_same<mathFunction_t, binaryMathFunctionFloat_t>::value, \
            output_t>::type mathFunction2Do(argument1_t argument1, argument2_t argument2, mathFunction_t function, \
                                            pfloatRoundingMethod_enum rounding_method, \
                                            uint32_t FP32MantissaMask) {                  \
            float argument1_f = pfloat_sourceTOtarget_scalarMath(input1, TO, float)(argument1); \
            float argument2_f = pfloat_sourceTOtarget_scalarMath(input2, TO, float)(argument2); \
            float temp = truncateMantissa((function)(argument1_f, argument2_f), FP32MantissaMask); \
            return pfloat_sourceTOtarget_scalarMath(float, TO, output)(temp, rounding_method); \
    }

    // ------------------------------------------
    // Functions with one argument

    pfloat_createSingleArgumentMathFunction(pfloat8,pfloat8)
    pfloat_createSingleArgumentMathFunction(pfloat8,pfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat8,upfloat8high)
    pfloat_createSingleArgumentMathFunction(pfloat8,upfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat8,pfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat8,pfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat8,upfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat8,upfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat8,pfloat16)
    pfloat_createSingleArgumentMathFunction(pfloat8,float)

    pfloat_createSingleArgumentMathFunction(pfloat8low,pfloat8)
    pfloat_createSingleArgumentMathFunction(pfloat8low,pfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat8low,upfloat8high)
    pfloat_createSingleArgumentMathFunction(pfloat8low,upfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat8low,pfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat8low,pfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat8low,upfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat8low,upfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat8low,pfloat16)
    pfloat_createSingleArgumentMathFunction(pfloat8low,float)

    pfloat_createSingleArgumentMathFunction(upfloat8high,pfloat8)
    pfloat_createSingleArgumentMathFunction(upfloat8high,pfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat8high,upfloat8high)
    pfloat_createSingleArgumentMathFunction(upfloat8high,upfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat8high,pfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat8high,pfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat8high,upfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat8high,upfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat8high,pfloat16)
    pfloat_createSingleArgumentMathFunction(upfloat8high,float)

    pfloat_createSingleArgumentMathFunction(upfloat8low,pfloat8)
    pfloat_createSingleArgumentMathFunction(upfloat8low,pfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat8low,upfloat8high)
    pfloat_createSingleArgumentMathFunction(upfloat8low,upfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat8low,pfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat8low,pfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat8low,upfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat8low,upfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat8low,pfloat16)
    pfloat_createSingleArgumentMathFunction(upfloat8low,float)

    pfloat_createSingleArgumentMathFunction(pfloat16high,pfloat8)
    pfloat_createSingleArgumentMathFunction(pfloat16high,pfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16high,upfloat8high)
    pfloat_createSingleArgumentMathFunction(pfloat16high,upfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16high,pfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16high,pfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16high,upfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16high,upfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16high,pfloat16)
    pfloat_createSingleArgumentMathFunction(pfloat16high,float)

    pfloat_createSingleArgumentMathFunction(pfloat16low,pfloat8)
    pfloat_createSingleArgumentMathFunction(pfloat16low,pfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16low,upfloat8high)
    pfloat_createSingleArgumentMathFunction(pfloat16low,upfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16low,pfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16low,pfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16low,upfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16low,upfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16low,pfloat16)
    pfloat_createSingleArgumentMathFunction(pfloat16low,float)

    pfloat_createSingleArgumentMathFunction(upfloat16high,pfloat8)
    pfloat_createSingleArgumentMathFunction(upfloat16high,pfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat16high,upfloat8high)
    pfloat_createSingleArgumentMathFunction(upfloat16high,upfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat16high,pfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat16high,pfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat16high,upfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat16high,upfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat16high,pfloat16)
    pfloat_createSingleArgumentMathFunction(upfloat16high,float)

    pfloat_createSingleArgumentMathFunction(upfloat16low,pfloat8)
    pfloat_createSingleArgumentMathFunction(upfloat16low,pfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat16low,upfloat8high)
    pfloat_createSingleArgumentMathFunction(upfloat16low,upfloat8low)
    pfloat_createSingleArgumentMathFunction(upfloat16low,pfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat16low,pfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat16low,upfloat16high)
    pfloat_createSingleArgumentMathFunction(upfloat16low,upfloat16low)
    pfloat_createSingleArgumentMathFunction(upfloat16low,pfloat16)
    pfloat_createSingleArgumentMathFunction(upfloat16low,float)

    pfloat_createSingleArgumentMathFunction(pfloat16,pfloat8)
    pfloat_createSingleArgumentMathFunction(pfloat16,pfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16,upfloat8high)
    pfloat_createSingleArgumentMathFunction(pfloat16,upfloat8low)
    pfloat_createSingleArgumentMathFunction(pfloat16,pfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16,pfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16,upfloat16high)
    pfloat_createSingleArgumentMathFunction(pfloat16,upfloat16low)
    pfloat_createSingleArgumentMathFunction(pfloat16,pfloat16)
    pfloat_createSingleArgumentMathFunction(pfloat16,float)

    pfloat_createSingleArgumentMathFunction(float,pfloat8)
    pfloat_createSingleArgumentMathFunction(float,pfloat8low)
    pfloat_createSingleArgumentMathFunction(float,upfloat8high)
    pfloat_createSingleArgumentMathFunction(float,upfloat8low)
    pfloat_createSingleArgumentMathFunction(float,pfloat16high)
    pfloat_createSingleArgumentMathFunction(float,pfloat16low)
    pfloat_createSingleArgumentMathFunction(float,upfloat16high)
    pfloat_createSingleArgumentMathFunction(float,upfloat16low)
    pfloat_createSingleArgumentMathFunction(float,pfloat16)
    pfloat_createSingleArgumentMathFunction(float,float)

    template<class output_t, class argument_t, typename mathFunction_t>
    output_t pfloatMathFunction(argument_t argument, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method,
                          uint32_t FP32MantissaMask) {
        return mathFunctionDo<output_t, argument_t, mathFunction_t>(argument, function,
                                                                    rounding_method, FP32MantissaMask);
    }

    // ------------------------------------------
    // Functions with two arguments

    // We remind us: pfloat_createTwoArgumentMathFunction(input1, input2, output)
    pfloat_createTwoArgumentMathFunction(pfloat8, pfloat8, pfloat8)
    pfloat_createTwoArgumentMathFunction(pfloat8, pfloat8low, pfloat8)
    pfloat_createTwoArgumentMathFunction(pfloat8, pfloat8, float)
    pfloat_createTwoArgumentMathFunction(pfloat8, pfloat8low, float)
    pfloat_createTwoArgumentMathFunction(pfloat8, pfloat8, pfloat16)
    pfloat_createTwoArgumentMathFunction(upfloat8low, pfloat8, pfloat16)
    pfloat_createTwoArgumentMathFunction(upfloat8low, upfloat8high, pfloat16)
    pfloat_createTwoArgumentMathFunction(pfloat16, pfloat16, pfloat16)
    pfloat_createTwoArgumentMathFunction(pfloat16, pfloat16, float)
    pfloat_createTwoArgumentMathFunction(float, float, float)
    // TODO: Consider to implement other 'reasonable' type combinations to be added to the list above....

    template<class output_t, class argument_t, class argument2_t, typename mathFunction_t>
    output_t pfloatMathFunction(argument_t argument1, argument2_t argument2, mathFunction_t function,
                          pfloatRoundingMethod_enum rounding_method,
                          uint32_t FP32MantissaMask) {
        return mathFunction2Do<output_t, argument_t, argument2_t, mathFunction_t>(argument1, argument2, function,
                                                                                 rounding_method, FP32MantissaMask);
    }

} // end namespace pfloat_n


#endif // PFLOAT_PFLOAT_TEMPLATED_SCALAR_MATH_H

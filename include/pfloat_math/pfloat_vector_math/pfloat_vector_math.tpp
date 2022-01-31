#ifndef PFLOAT_PFLOAT_TEMPLATED_VECTOR_MATH_TPP
#define PFLOAT_PFLOAT_TEMPLATED_VECTOR_MATH_TPP

// Note that some of our types are aligned (read: have attributes).
// We don't need/want to see the related warnings that type checking (via std::is_same<...>) in
// the various templates below are not including the attributes in the type comparison
#pragma GCC diagnostic ignored "-Wignored-attributes"

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    // ==========================================================
    // TEMPLATE DEFINITIONS

    // Note: Vectors must have binary number of elements (read: vector size must be 2,4,8,16,32 or 64)

    // For all N do (input1[N] + input2[N])*scale
    template <class return_t, class input1_t, class input2_t = input1_t>
    void pfloatAdd(return_t output, input1_t input1, input2_t input2,
                               float scale = 1.0f,
                               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                               uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask);

    // For all N do (input1[N] - input2[N])*scale
    template <class return_t, class input1_t, class input2_t = input1_t>
    void pfloatSub(return_t output, input1_t input1, input2_t input2,
                   float scale = 1.0f,
                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                   uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask);

    // sumOverN(input[N])*scale
    template <class return_t, class input_t>
    return_t pfloatAccumulate(input_t input,
                                float scale = 1.0f,
                                pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                                uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask);

    // sumOverN(input[N]*input[N])*scale
    template <class return_t, class input_t>
    return_t pfloatSumOfSquares(input_t input,
                                float scale = 1.0f,
                                pfloatRoundingMethod_enum rounding_method_mult = pfloat_DefaultRoundingMethod,
                                uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask,
                                uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask);

    // sumOverN(input1[N] * input2[N])*scale
    template <class return_t, class input1_t, class input2_t = input1_t>
    return_t pfloatMultiplyAdd(input1_t input1, input2_t input2,
                               float scale = 1.0f,
                               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                               uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask,
                               uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask);

    // sumOverN((input1[N]-input2[N])^2)*scale - C
    template <class return_t, class input1_t, class input2_t = input1_t, class constant_t>
    return_t pfloatSumSquaresOfDeltaMinusC(input1_t input1, input2_t input2,
                                   constant_t C = 0,
                                   float scale = 1.0f,
                                   pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                                   uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask,
                                   uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask);


    // ==========================================================
    // TEMPLATE IMPLEMENTATIONS

    // ----------------------------------------------------------
    // HELPER FOR TRUNCATING THE LSBs OF A FLOAT

    inline void pfloatVectorsTruncateMantissa(float& input, const uint32_t FP32MantissaMask) {
        // truncate the bits
        uint32_t tempTruncated = ((*(uint32_t *)&input) & FP32MantissaMask);
        input = (*(float *)& tempTruncated);
    }

    // ----------------------------------------------------------
    // HELPER DEFINES

#define pfloat_vectors_vectorType(base_t, underscore, vectorsize, _t) base_t##underscore##vectorsize##_t
#define pfloat_vectors_vectorClass(base_t, underscore, vectorsize) base_t##underscore##vectorsize
// Remark: Using 'vectorsize' frees us from checking type compatibility: If vector sizes don't match, it won't compile
#define pfloat_vectors_vectorSize(vectorsize) vectorsize
#define pfloat_vectors_sourceTOtarget(source, TO, target) source##TO##target


    // ----------------------------------------------------------
    // ELEMENTWISE ADD ELEMENTS OF TWO VECTORS

// macro to create templated add functions for various type combinations
#define pfloat_vectors_createAdd(base_output_t, base1_t, base2_t, vectorsize) \
template <class return_t, class input1_t, class input2_t> \
typename std::enable_if<( \
         (std::is_same<input1_t, pfloat_vectors_vectorType(base1_t, _, vectorsize, _t) >::value || \
         std::is_same<input1_t, pfloat_vectors_vectorClass(base1_t, _, vectorsize) >::value) && \
         (std::is_same<input2_t, pfloat_vectors_vectorType(base2_t, _, vectorsize, _t) >::value || \
         std::is_same<input2_t, pfloat_vectors_vectorClass(base2_t, _, vectorsize) >::value) && \
         (std::is_same<return_t, pfloat_vectors_vectorType(base_output_t, _, vectorsize, _t) >::value || \
         std::is_same<return_t, pfloat_vectors_vectorClass(base_output_t, _, vectorsize) >::value) && \
         (((vectorsize) % 2) == 0) ), \
         void>::type addDo(return_t output, const input1_t input1, const input2_t input2, \
                                        float scale = 1.0f, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod, \
                                        uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) { \
    float a, b; \
    float result_f; \
    for (int i=0; i<(pfloat_vectors_vectorSize(vectorsize)); i++) {         \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[i]);          \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&input2[i]);          \
        result_f = truncateMantissa(a+b, FP32MantissaMask);              \
        result_f = truncateMantissa(result_f * scale, FP32MantissaMask);              \
        output[i] = pfloat_vectors_sourceTOtarget(float, TO, base_output_t)(result_f);                                                                 \
    }                                                                          \
}

    // Create the various addition functions for a selected set of input and output types
    pfloat_vectors_createAdd(pfloat16, pfloat8high, pfloat8low, 64)
    pfloat_vectors_createAdd(pfloat, pfloat8high, pfloat8high, 4)
    pfloat_vectors_createAdd(pfloat, pfloat8high, pfloat8high, 64)
    pfloat_vectors_createAdd(pfloat, pfloat, pfloat, 4)
    pfloat_vectors_createAdd(pfloat, pfloat, pfloat, 64)
    pfloat_vectors_createAdd(pfloat8low, pfloat8high, pfloat8high, 64)
    pfloat_vectors_createAdd(upfloat8low, pfloat8high, pfloat8high, 64)
    // TODO: Create more of those functions as deemed relevant

    template <class return_t, class input1_t, class input2_t>
    void pfloatAdd(return_t output, input1_t input1, input2_t input2,
                               float scale,
                               pfloatRoundingMethod_enum rounding_method,
                               uint32_t FP32MantissaMask) {
        assert(((FP32MantissaMask & 0xFFF80000) == 0xFFF80000) && "Invalid Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMask) == __builtin_popcount(~FP32MantissaMask) && "Invalid Mantissa Mask");
        addDo<return_t, input1_t, input2_t>(output, input1, input2, scale, rounding_method, FP32MantissaMask);
    }


    // ----------------------------------------------------------
    // ELEMENTWISE SUBTRACT ELEMENTS OF TWO VECTORS

// macro to create templated subtract functions for various type combinations
#define pfloat_vectors_createSub(base_output_t, base1_t, base2_t, vectorsize) \
template <class return_t, class input1_t, class input2_t> \
typename std::enable_if<( \
         (std::is_same<input1_t, pfloat_vectors_vectorType(base1_t, _, vectorsize, _t) >::value || \
         std::is_same<input1_t, pfloat_vectors_vectorClass(base1_t, _, vectorsize) >::value) && \
         (std::is_same<input2_t, pfloat_vectors_vectorType(base2_t, _, vectorsize, _t) >::value || \
         std::is_same<input2_t, pfloat_vectors_vectorClass(base2_t, _, vectorsize) >::value) && \
         (std::is_same<return_t, pfloat_vectors_vectorType(base_output_t, _, vectorsize, _t) >::value || \
         std::is_same<return_t, pfloat_vectors_vectorClass(base_output_t, _, vectorsize) >::value) && \
         (((vectorsize) % 2) == 0) ), \
         void>::type subDo(return_t output, const input1_t input1, const input2_t input2, \
                                        float scale = 1.0f, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod, \
                                        uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) { \
    float a, b; \
    float result_f; \
    for (int i=0; i<(pfloat_vectors_vectorSize(vectorsize)); i++) {         \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[i]);          \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&input2[i]);          \
        result_f = truncateMantissa(a-b, FP32MantissaMask);              \
        result_f = truncateMantissa(result_f * scale, FP32MantissaMask);                          \
        output[i] = pfloat_vectors_sourceTOtarget(float, TO, base_output_t)(result_f);             \
    }                                                                          \
}

    // Create the various subtraction functions for a selected set of input and output types
    pfloat_vectors_createSub(pfloat16, pfloat8high, pfloat8low, 64)
    pfloat_vectors_createSub(pfloat, pfloat8high, pfloat8high, 4)
    pfloat_vectors_createSub(pfloat, pfloat8high, pfloat8high, 64)
    pfloat_vectors_createSub(pfloat, pfloat, pfloat, 4)
    pfloat_vectors_createSub(pfloat, pfloat, pfloat, 64)
    pfloat_vectors_createSub(pfloat8low, pfloat8high, pfloat8high, 64)
    // TODO: Create more of those functions as deemed relevant

    template <class return_t, class input1_t, class input2_t>
    void pfloatSub(return_t output, input1_t input1, input2_t input2,
                       float scale,
                       pfloatRoundingMethod_enum rounding_method,
                       uint32_t FP32MantissaMask) {
        assert(((FP32MantissaMask & 0xFFF80000) == 0xFFF80000) && "Invalid Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMask) == __builtin_popcount(~FP32MantissaMask) && "Invalid Mantissa Mask");
        subDo<return_t, input1_t, input2_t>(output, input1, input2, scale, rounding_method, FP32MantissaMask);
    }


    // ----------------------------------------------------------
    // ACCUMULATE ELEMENTS OF A VECTOR

// macro to create templated accumulate functions for various type combinations
#define pfloat_vectors_createAccumulate(output_t, base1_t, vectorsize) \
template <class return_t, class input1_t> \
typename std::enable_if<( \
         (std::is_same<input1_t, pfloat_vectors_vectorType(base1_t, _, vectorsize, _t) >::value || \
         std::is_same<input1_t, pfloat_vectors_vectorClass(base1_t, _, vectorsize) >::value) && \
         std::is_same<return_t, output_t>::value && (((vectorsize) % 2) == 0) ), \
         return_t>::type accumulateDo(const input1_t input1, \
                                        float scale = 1.0f, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod, \
                                        uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) { \
    float a, b; \
    float result_f; \
    float temp_result[pfloat_vectors_vectorSize(vectorsize) /2]; \
    for (int i=0; i<(pfloat_vectors_vectorSize(vectorsize) /2); i++) {         \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[2*i]);          \
        b = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[2*i+1]);          \
        temp_result[i] = truncateMantissa(a+b, FP32MantissaMask); \
    }                                                                          \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /4); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /8); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /16); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /32); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /64); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);  \
    result_f = truncateMantissa(temp_result[0] * scale, FP32MantissaMask);                         \
    return pfloat_vectors_sourceTOtarget(float, TO, output_t)(result_f, rounding_method); \
}

    // Create the various accumulate functions for a selected set of input and output types
    pfloat_vectors_createAccumulate(pfloat, pfloat8high, 64)
    pfloat_vectors_createAccumulate(pfloat16, pfloat8high, 64)
    pfloat_vectors_createAccumulate(pfloat, pfloat, 64)
    pfloat_vectors_createAccumulate(pfloat, pfloat8low, 64)
    pfloat_vectors_createAccumulate(pfloat, upfloat8low, 64)
    // TODO: Create more of those functions as deemed relevant

    template <class return_t, class input_t>
    return_t pfloatAccumulate(input_t input,
                               float scale,
                               pfloatRoundingMethod_enum rounding_method,
                               uint32_t FP32MantissaMask) {
        assert(((FP32MantissaMask & 0xFFF80000) == 0xFFF80000) && "Invalid Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMask) == __builtin_popcount(~FP32MantissaMask) && "Invalid Mantissa Mask");
        return accumulateDo<return_t, input_t>(input, scale, rounding_method, FP32MantissaMask);
    }


    // ----------------------------------------------------------
    // MULTIPLY ADD

// macro to create templated multiply add functions for various type combinations
#define pfloat_vectors_createMultiplyAdd(output_t, base1_t, base2_t, vectorsize) \
template <class return_t, class input1_t, class input2_t> \
typename std::enable_if<( \
         (std::is_same<input1_t, pfloat_vectors_vectorType(base1_t, _, vectorsize, _t) >::value || \
         std::is_same<input1_t, pfloat_vectors_vectorClass(base1_t, _, vectorsize) >::value) && \
         (std::is_same<input2_t, pfloat_vectors_vectorType(base2_t, _, vectorsize, _t) >::value || \
         std::is_same<input2_t, pfloat_vectors_vectorClass(base2_t, _, vectorsize) >::value) && \
         std::is_same<return_t, output_t>::value && (((vectorsize) % 2) == 0) ), \
         return_t>::type multiplyAddDo(const input1_t input1, const input2_t input2, \
                                        float scale = 1.0f, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod, \
                                        uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask, \
                                        uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask) { \
    float a, b, mult1, mult2, add; \
    float result_f; \
    float temp_result[pfloat_vectors_vectorSize(vectorsize) /2]; \
    for (int i=0; i<(pfloat_vectors_vectorSize(vectorsize) /2); i++) {         \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&(input1[2*i]));          \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&(input2[2*i]));          \
        mult1 = a * b;                                                               \
        pfloatVectorsTruncateMantissa(mult1, FP32MantissaMaskMult); \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&(input1[2*i+1]));        \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&(input2[2*i+1]));        \
        mult2 = a * b;                                                               \
        pfloatVectorsTruncateMantissa(mult2, FP32MantissaMaskMult); \
        add = mult1 + mult2;                                                     \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd); \
        temp_result[i] = add;            \
    }                                                                          \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /4); i++){           \
        add = temp_result[2*i]+temp_result[2*i+1];                                \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);  \
        temp_result[i] = add;  \
    }                                                                             \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /8); i++){           \
        add = temp_result[2*i]+temp_result[2*i+1];                                \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);  \
        temp_result[i] = add;  \
    }                                                                             \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /16); i++){           \
        add = temp_result[2*i]+temp_result[2*i+1];                                \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);  \
        temp_result[i] = add;  \
    }                                                                             \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /32); i++){           \
        add = temp_result[2*i]+temp_result[2*i+1];                                \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);  \
        temp_result[i] = add;  \
    }                                                                             \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /64); i++){           \
        add = temp_result[2*i]+temp_result[2*i+1];                                \
        pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);  \
        temp_result[i] = add;  \
    }                                                                             \
    result_f = temp_result[0] * scale;       \
    pfloatVectorsTruncateMantissa(result_f, FP32MantissaMaskMult);  \
    return pfloat_vectors_sourceTOtarget(float, TO, output_t)(result_f, rounding_method); \
}

    // Create the various multiply-add functions for [a selected set of] input and output types
    pfloat_vectors_createMultiplyAdd(pfloat16high, upfloat8high, pfloat8low, 64);
    pfloat_vectors_createMultiplyAdd(pfloat16high, upfloat8high, upfloat8high, 64);
    pfloat_vectors_createMultiplyAdd(pfloat16high, pfloat8low, pfloat8low, 64);

    pfloat_vectors_createMultiplyAdd(pfloat16, pfloat8high, pfloat8low, 64)
    pfloat_vectors_createMultiplyAdd(pfloat, pfloat8high, pfloat8high, 4)
    pfloat_vectors_createMultiplyAdd(pfloat, pfloat8high, pfloat8high, 64)
    pfloat_vectors_createMultiplyAdd(pfloat, pfloat, pfloat, 4)
    pfloat_vectors_createMultiplyAdd(pfloat, pfloat, pfloat, 64)
    pfloat_vectors_createMultiplyAdd(pfloat, pfloat8low, pfloat8low, 64)
    pfloat_vectors_createMultiplyAdd(float, pfloat, pfloat, 64)
    // TODO: Create more of those functions as deemed relevant

    template <class return_t, class input1_t, class input2_t>
    return_t pfloatMultiplyAdd(input1_t input1, input2_t input2,
                            float scale,
                            pfloatRoundingMethod_enum rounding_method,
                            uint32_t FP32MantissaMaskMult,
			                uint32_t FP32MantissaMaskAdd) {
        assert(((FP32MantissaMaskMult & 0xFFF80000) == 0xFFF80000) && "Invalid Multiplication Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMaskMult) == __builtin_popcount(~FP32MantissaMaskMult) &&
               "Invalid Multiplication Mantissa Mask");
        assert(((FP32MantissaMaskAdd & 0xFFF80000) == 0xFFF80000) && "Invalid Addition Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMaskAdd) == __builtin_popcount(~FP32MantissaMaskAdd) &&
               "Invalid Addition Mantissa Mask");
        return multiplyAddDo<return_t, input1_t, input2_t>(input1, input2,
                                                           scale,
                                                           rounding_method,
                                                           FP32MantissaMaskMult,FP32MantissaMaskAdd);
    }


    // ----------------------------------------------------------
    // SUM OF SQUARES

    template <class return_t, class input_t>
    return_t pfloatSumOfSquares(input_t input,
                                float scale,
                                pfloatRoundingMethod_enum rounding_method,
                                uint32_t FP32MantissaMaskMult,
				uint32_t FP32MantissaMaskAdd) {
        return pfloatMultiplyAdd<return_t, input_t, input_t>(input, input, scale, rounding_method, 
							     FP32MantissaMaskMult, FP32MantissaMaskAdd);
    }


    // ----------------------------------------------------------
    // SUM SQUARES OF DELTA MINUS C --> sum((a-b)^2) - C

    // macro to create templated multiply add functions for various type combinations
#define pfloat_vectors_createSumSquaresOfDeltaMinusC(output_t, base1_t, base2_t, const_t, vectorsize) \
template <class return_t, class input1_t, class input2_t, class constant_t> \
typename std::enable_if<( \
         (std::is_same<input1_t, pfloat_vectors_vectorType(base1_t, _, vectorsize, _t) >::value || \
         std::is_same<input1_t, pfloat_vectors_vectorClass(base1_t, _, vectorsize) >::value) && \
         (std::is_same<input2_t, pfloat_vectors_vectorType(base2_t, _, vectorsize, _t) >::value || \
         std::is_same<input2_t, pfloat_vectors_vectorClass(base2_t, _, vectorsize) >::value) && \
         std::is_same<constant_t, const_t>::value &&      \
         std::is_same<return_t, output_t>::value && (((vectorsize) % 2) == 0) ), \
         return_t>::type sumSquaresOfDeltaMinusCDo(const input1_t input1, const input2_t input2,   \
                                        constant_t C,                                                          \
                                        float scale = 1.0f, \
                                        pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod, \
                                        uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask, \
                                        uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask) { \
    float a, b, c, d; \
    float result_f; \
    float temp_result[pfloat_vectors_vectorSize(vectorsize) /2]; 		\
    for (int i=0; i<(pfloat_vectors_vectorSize(vectorsize) /2); i++) {         	\
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[2*i]);          \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&input2[2*i]);          \
        c = truncateMantissa(a-b, FP32MantissaMaskAdd);  \
        c = truncateMantissa(c*c, FP32MantissaMaskMult); \
        a = pfloat_vectors_sourceTOtarget(base1_t, TO, float)(*(base1_t *)&input1[2*i+1]);        \
        b = pfloat_vectors_sourceTOtarget(base2_t, TO, float)(*(base2_t *)&input2[2*i+1]);        \
        d = truncateMantissa(a-b, FP32MantissaMaskAdd);  \
        d = truncateMantissa(d*d, FP32MantissaMaskMult); \
        temp_result[i] = truncateMantissa(c + d, FP32MantissaMaskAdd);         \
    }                                                                          \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /4); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /8); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /16); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /32); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);  \
    for (int i=0; i<( pfloat_vectors_vectorSize(vectorsize) /64); i++)          \
        temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);  \
    result_f = truncateMantissa(temp_result[0] * scale, FP32MantissaMaskMult);                        \
    result_f = truncateMantissa(result_f - pfloat_vectors_sourceTOtarget(const_t, TO, float)(C), FP32MantissaMaskAdd);  \
    return pfloat_vectors_sourceTOtarget(float, TO, output_t)(result_f, rounding_method); \
}

    // Create the various 'sum of (squares of delta) minus constant' functions
    // for a selected set of input and output types
    pfloat_vectors_createSumSquaresOfDeltaMinusC(pfloat16, pfloat8high, pfloat8low, pfloat, 64)
    pfloat_vectors_createSumSquaresOfDeltaMinusC(pfloat, pfloat8high, pfloat8high, pfloat, 4)
    pfloat_vectors_createSumSquaresOfDeltaMinusC(pfloat, pfloat8high, pfloat8high, pfloat, 64)
    pfloat_vectors_createSumSquaresOfDeltaMinusC(pfloat, pfloat, pfloat, pfloat, 4)
    pfloat_vectors_createSumSquaresOfDeltaMinusC(pfloat, pfloat, pfloat, pfloat, 64)
    // TODO: Create more of those functions as deemed relevant


    template <class return_t, class input1_t, class input2_t, class constant_t>
    return_t pfloatSumSquaresOfDeltaMinusC(input1_t input1, input2_t input2,
                                    constant_t C,
                                    float scale,
                                    pfloatRoundingMethod_enum rounding_method,
                                    uint32_t FP32MantissaMaskMult,
                                    uint32_t FP32MantissaMaskAdd){
        assert(((FP32MantissaMaskMult & 0xFFF80000) == 0xFFF80000) && "Invalid Multiplication Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMaskMult) == __builtin_popcount(~FP32MantissaMaskMult) &&
               "Invalid Multiplication Mantissa Mask");
        assert(((FP32MantissaMaskAdd & 0xFFF80000) == 0xFFF80000) && "Invalid Addition Mantissa Mask");
        assert(__builtin_ctz(FP32MantissaMaskAdd) == __builtin_popcount(~FP32MantissaMaskAdd) &&
               "Invalid Addition Mantissa Mask");
        return sumSquaresOfDeltaMinusCDo<return_t, input1_t, input2_t, constant_t>(input1, input2,
                                                                                   C, scale,
                                                                                   rounding_method, 
                                                                                   FP32MantissaMaskMult,
                                                                                   FP32MantissaMaskAdd);
    }


} // end namespace pfloat_n

#endif //PFLOAT_PFLOAT_TEMPLATED_VECTOR_MATH_TPP

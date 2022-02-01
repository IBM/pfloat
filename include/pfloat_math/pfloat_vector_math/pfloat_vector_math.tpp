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

#define pfloatVectorMath_getBaseType(vector_variable) \
typename std::remove_cv<typename std::remove_reference<decltype(*(vector_variable))>::type>::type

    // ----------------------------------------------------------
    // ELEMENTWISE ADD ELEMENTS OF TWO VECTORS

    template <class return_t, class input1_t, class input2_t>
    void addDo(return_t output, const input1_t input1, const input2_t input2,
                                            float scale = 1.0f,
                                            pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                                            uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) {
        typedef pfloatVectorMath_getBaseType(input1) base1_t;
        typedef pfloatVectorMath_getBaseType(input2) base2_t;
        typedef pfloatVectorMath_getBaseType(output) base_return_t;
        static_assert(sizeof(input1_t)/sizeof(base1_t) == sizeof(input2_t)/sizeof(base2_t) &&
                      sizeof(return_t)/sizeof(base_return_t) == sizeof(input2_t)/sizeof(base2_t),
                      "Inconsistent vector sizes");
        const int vectorsize = sizeof(input1_t)/sizeof(base1_t);
        float a, b;
        float result_f;
        for (int i=0; i<vectorsize; i++) {
            a = pfloat2float<base1_t>(*(base1_t *)&input1[i]);
            b = pfloat2float<base2_t>(*(base2_t *)&input2[i]);
            result_f = truncateMantissa(a+b, FP32MantissaMask);
            result_f = truncateMantissa(result_f * scale, FP32MantissaMask);
            output[i] = pfloat2float<base_return_t>(result_f, rounding_method);
        }
    }

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

    template <class return_t, class input1_t, class input2_t>
    void subDo(return_t output, const input1_t input1, const input2_t input2,
               float scale = 1.0f,
               pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
               uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) {
        typedef pfloatVectorMath_getBaseType(input1) base1_t;
        typedef pfloatVectorMath_getBaseType(input2) base2_t;
        typedef pfloatVectorMath_getBaseType(output) base_return_t;
        static_assert(sizeof(input1_t)/sizeof(base1_t) == sizeof(input2_t)/sizeof(base2_t) &&
                      sizeof(return_t)/sizeof(base_return_t) == sizeof(input2_t)/sizeof(base2_t),
                      "Inconsistent vector sizes");
        const int vectorsize = sizeof(input1_t)/sizeof(base1_t);
        float a, b;
        float result_f;
        for (int i=0; i<vectorsize; i++) {
            a = pfloat2float<base1_t>(*(base1_t *)&input1[i]);
            b = pfloat2float<base2_t>(*(base2_t *)&input2[i]);
            result_f = truncateMantissa(a-b, FP32MantissaMask);
            result_f = truncateMantissa(result_f * scale, FP32MantissaMask);
            output[i] = float2pfloat<base_return_t>(result_f, rounding_method);
        }
    }

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

    template <class return_t, class input1_t>
    return_t accumulateDo(const input1_t input1,
                          float scale = 1.0f,
                          pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                          uint32_t FP32MantissaMask = pfloat_DefaultFP32MantissaMask) {
        typedef pfloatVectorMath_getBaseType(input1) base1_t;
        const int vectorsize = sizeof(input1_t)/sizeof(base1_t);
        float a, b;
        float result_f;
        float temp_result[vectorsize/2];
        for (int i=0; i<(vectorsize/2); i++) {
            a = pfloat2float<base1_t>(*(base1_t *)&input1[2*i]);
            b = pfloat2float<base1_t>(*(base1_t *)&input1[2*i+1]);
            temp_result[i] = truncateMantissa(a+b, FP32MantissaMask);
        }
        for (int i=0; i<(vectorsize/4); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);
        for (int i=0; i<(vectorsize/8); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);
        for (int i=0; i<(vectorsize/16); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);
        for (int i=0; i<(vectorsize/32); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);
        for (int i=0; i<(vectorsize/64); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMask);
        result_f = truncateMantissa(temp_result[0] * scale, FP32MantissaMask);
        return float2pfloat<return_t>(result_f, rounding_method);
    }

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

    template <class return_t, class input1_t, class input2_t>
    return_t multiplyAddDo(const input1_t input1, const input2_t input2,
                           float scale = 1.0f,
                           pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                           uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask,
                           uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask) {
        typedef pfloatVectorMath_getBaseType(input1) base1_t;
        typedef pfloatVectorMath_getBaseType(input2) base2_t;
        static_assert(sizeof(input1_t)/sizeof(base1_t) == sizeof(input2_t)/sizeof(base2_t),
                      "Inconsistent vector sizes");
        const int vectorsize = sizeof(input1_t)/sizeof(base1_t);
        float a, b, mult1, mult2, add;
        float result_f;
        float temp_result[vectorsize / 2];
        for (int i=0; i< (vectorsize  / 2); i++) {
            a = pfloat2float<base1_t>((input1[2*i]));
            b = pfloat2float<base2_t>((input2[2*i]));
            mult1 = a * b;
            pfloatVectorsTruncateMantissa(mult1, FP32MantissaMaskMult);
            a = pfloat2float<base1_t>((input1[2*i+1]));
            b = pfloat2float<base2_t>((input2[2*i+1]));
            mult2 = a * b;
            pfloatVectorsTruncateMantissa(mult2, FP32MantissaMaskMult);
            add = mult1 + mult2;
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        for (int i=0; i<(vectorsize / 4); i++){
            add = temp_result[2*i]+temp_result[2*i+1];
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        for (int i=0; i<(vectorsize / 8); i++){
            add = temp_result[2*i]+temp_result[2*i+1];
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        for (int i=0; i<(vectorsize / 16); i++){
            add = temp_result[2*i]+temp_result[2*i+1];
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        for (int i=0; i<(vectorsize / 32); i++){
            add = temp_result[2*i]+temp_result[2*i+1];
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        for (int i=0; i<(vectorsize / 64); i++){
            add = temp_result[2*i]+temp_result[2*i+1];
            pfloatVectorsTruncateMantissa(add, FP32MantissaMaskAdd);
            temp_result[i] = add;
        }
        result_f = temp_result[0] * scale;
        pfloatVectorsTruncateMantissa(result_f, FP32MantissaMaskMult);
        return float2pfloat<return_t>(result_f, rounding_method);
    }

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

    template <class return_t, class input1_t, class input2_t, class constant_t>
    return_t sumSquaresOfDeltaMinusCDo(const input1_t input1, const input2_t input2,
                                            constant_t C,
                                            float scale = 1.0f,
                                            pfloatRoundingMethod_enum rounding_method = pfloat_DefaultRoundingMethod,
                                            uint32_t FP32MantissaMaskMult = pfloat_DefaultFP32MantissaMask,
                                            uint32_t FP32MantissaMaskAdd = pfloat_DefaultFP32MantissaMask) {
        typedef pfloatVectorMath_getBaseType(input1) base1_t;
        typedef pfloatVectorMath_getBaseType(input2) base2_t;
        static_assert(sizeof(input1_t)/sizeof(base1_t) == sizeof(input2_t)/sizeof(base2_t),
                      "Inconsistent vector sizes");
        const int vectorsize = sizeof(input1_t)/sizeof(base1_t);
        float a, b, c, d;
        float result_f;
        float temp_result[vectorsize/2];
        for (int i=0; i<(vectorsize/2); i++) {
            a = pfloat2float<base1_t>(*(base1_t *)&input1[2*i]);
            b = pfloat2float<base2_t>(*(base2_t *)&input2[2*i]);
            c = truncateMantissa(a-b, FP32MantissaMaskAdd);
            c = truncateMantissa(c*c, FP32MantissaMaskMult);
            a = pfloat2float<base1_t>(*(base1_t *)&input1[2*i+1]);
            b = pfloat2float<base2_t>(*(base2_t *)&input2[2*i+1]);
            d = truncateMantissa(a-b, FP32MantissaMaskAdd);
            d = truncateMantissa(d*d, FP32MantissaMaskMult);
            temp_result[i] = truncateMantissa(c + d, FP32MantissaMaskAdd);
        }
        for (int i=0; i<(vectorsize/4); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);
        for (int i=0; i<(vectorsize/8); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);
        for (int i=0; i<(vectorsize/16); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);
        for (int i=0; i<(vectorsize/32); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);
        for (int i=0; i<(vectorsize/64); i++)
            temp_result[i] = truncateMantissa(temp_result[2*i]+temp_result[2*i+1], FP32MantissaMaskAdd);
        result_f = truncateMantissa(temp_result[0] * scale, FP32MantissaMaskMult);
        result_f = truncateMantissa(result_f - pfloat2float<constant_t>(C), FP32MantissaMaskAdd);
        return float2pfloat<return_t>(result_f, rounding_method);
    }


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

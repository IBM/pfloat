#include <iostream>
#include <cassert>
#include <cmath>


#include "pfloat.h"


using namespace pfloat_n;

// Simple 8-bit random number generator (= a well known 32-bit LCG of which we use bits [20..27])
inline uint8_t getRandom8(uint32_t& state) {return (((state = state * 32310901u + 1013904223u) >> 20) & 0xFF);}

int main() {


    pfloat16 result;
    pfloat8high operand1 = 0.25;
    pfloat8low operand2 = 0.0625;
    upfloat8low operand3 = 0.01;

    fprintf(stdout, "operand1 = 0x%x = %.6f\n", operand1.get(), pfloat2ieee<pfloat8high, float>(operand1));
    fprintf(stdout, "operand2 = 0x%x = %.6f\n", operand2.get(), pfloat2ieee<pfloat8low, float>(operand2));
    fprintf(stdout, "operand3 = 0x%x = %.6f\n", operand3.get(), pfloat2ieee<upfloat8low, float>(operand3));

    result = (pfloat)15.0f * (operand1 + operand2 -
             pfloatMathFunction<upfloat8high>((operand3 + 0.02), sqrtf));

    fprintf(stdout, "CHAINED MATH TEST: result = 0x%x = %.6f\n\n", result.get(), pfloat2ieee<pfloat16, float>(result));

    // check clipping to 1.0
    pfloat16 convsource = 2.0;
    auto conv1 = pfloat2ieee<pfloat8high, float>(convsource);
    auto conv2 = pfloat2float<pfloat16>(convsource);
    fprintf(stdout, "CLIPPING TEST: %.6e, %.6e\n\n", conv1, conv2);

    // Single argument math function test
    auto result_sqrtf_pfloat = pfloatMathFunction<upfloat8high, upfloat16low>(0.2, sqrtf);
    fprintf(stdout, "SQRTF: via float --> %.6e, via pfloat --> %.6e\n",
            sqrtf(0.2), pfloat2float<upfloat8high>(result_sqrtf_pfloat));

    // Two argument math function test
    auto result_atan2f_pfloat16 = pfloatMathFunction<pfloat16, upfloat8low, pfloat8high>
            (float2pfloat<upfloat8low>(0.30), 0.02, atan2f);
    auto result_atan2f_float = atan2f
            (0.30, 0.02);
    fprintf(stdout, "ATAN2: via float --> %.6e, via pfloat --> %.6e\n\n",
            result_atan2f_float, pfloat2float<pfloat16>(result_atan2f_pfloat16));


    // Vector math tests
    fprintf(stdout, "VECTOR MATH TESTS\n");
    fprintf(stdout, "Note: Errors > 1%% only for small magnitudes of results as expected\n");

    uint32_t randState = 123456789;
    upfloat8high_64_t vector1;
    pfloat8low_64_t vector2;
    const float scalingFactor = 0.015625;

    for (int loop = 0; loop < 100000; loop++) { // run many experiments

        // prepare two pfloat vectors (and a float to hold the 'exact' result)
        float multiplyAddResult_float = 0.0f;
        float accumulateResult_upfloat8high_f = 0.0f;
        float accumulateResult_pfloat8low_f = 0.0f;
        float sumOfSquaresResult_upfloat8high_f = 0.0f;
        float sumOfSquaresResult_pfloat8low_f = 0.0f;
        // initialize vector with 'random' 8 bit values ...
        for (int i = 0; i < 64; i++) {
            vector1[i].set(getRandom8(randState));
            vector2[i].set(getRandom8(randState));
            // ... and do an on-the-fly calculation of the float versions (for accuracy comparisons)
            multiplyAddResult_float += (scalingFactor *
                    pfloat2ieee<upfloat8high, float>(vector1[i]) * pfloat2ieee<pfloat8low, float>(vector2[i])) ;
            sumOfSquaresResult_upfloat8high_f += (scalingFactor *
                                                pfloat2ieee<upfloat8high, float>(vector1[i]) *
                                                pfloat2ieee<upfloat8high, float>(vector1[i])) ;
            sumOfSquaresResult_pfloat8low_f += (scalingFactor *
                                                pfloat2ieee<pfloat8low, float>(vector2[i]) *
                                                pfloat2ieee<pfloat8low, float>(vector2[i])) ;
            accumulateResult_upfloat8high_f += (scalingFactor * pfloat2ieee<upfloat8high, float>(vector1[i]));
            accumulateResult_pfloat8low_f += (scalingFactor * pfloat2ieee<pfloat8low, float>(vector2[i]));
        }

        // execute multiply add function (including scaling and reduced bit-size math)
        auto multiplyAddResult_pfloat = pfloatMultiplyAdd<pfloat16high, upfloat8high_64_t, pfloat8low_64_t>
                (vector1, vector2,
                 scalingFactor,
                 pfloat_n::nearest,
                 0xFFFFF800,
                 0xFFFFFF80);

        auto accumulateResult_upfloat8high_pfloat = pfloatAccumulate<pfloat16, upfloat8high_64_t>(vector1, scalingFactor);
        auto accumulateResult_pfloat8low_pfloat = pfloatAccumulate<pfloat16,pfloat8low_64_t>(vector2, scalingFactor);

        // execute sum of squares function (including scaling and reduced bit-size math)
        auto sumOfSquaresResult_upfloat8high_p = pfloatSumOfSquares<pfloat16high, upfloat8high_64_t>
                (vector1,
                 scalingFactor,
                 pfloat_n::nearest,
                 0xFFFFF800,
                 0xFFFFFF80);
        auto sumOfSquaresResult_pfloat8low_p = pfloatSumOfSquares<pfloat16high, pfloat8low_64_t>
                (vector2,
                 scalingFactor,
                 pfloat_n::nearest,
                 0xFFFFF800,
                 0xFFFFFF80);

        // show results (and compare with 'exact' value determined via 32-bit float)
        pfloat percentageErrorMultiplyAdd =
                100.0f * ((pfloat2ieee<pfloat16high, float>(multiplyAddResult_pfloat) - multiplyAddResult_float) /
                       multiplyAddResult_float);
        if (std::abs(percentageErrorMultiplyAdd.get()) > 1.0)
            fprintf(stdout, "MULTADD[%d]: pfloat --> %.6e,\t float -->  %.6e, \terror = %.2f %% \n",
                    loop,
                    pfloat2ieee<pfloat16high, float>(multiplyAddResult_pfloat),
                    multiplyAddResult_float, percentageErrorMultiplyAdd.get() );

        pfloat percentageErrorAccumulate =
                100.0f * ((pfloat2float<pfloat16high>(accumulateResult_upfloat8high_pfloat) - accumulateResult_upfloat8high_f) /
                          accumulateResult_upfloat8high_f);
        if (std::abs(percentageErrorAccumulate.get()) > 1.0)
            fprintf(stdout, "ACCUMULATE pfloat16high [%d]: pfloat --> %.6e,\t float -->  %.6e, \terror = %.2f %% \n",
                    loop,
                    pfloat2float<pfloat16high>(accumulateResult_upfloat8high_pfloat),
                    accumulateResult_upfloat8high_f, percentageErrorAccumulate.get() );
        percentageErrorAccumulate =
                100.0f * ((pfloat2float<pfloat16high>(accumulateResult_pfloat8low_pfloat) - accumulateResult_pfloat8low_f) /
                          accumulateResult_pfloat8low_f);
        if (std::abs(percentageErrorAccumulate.get()) > 1.0)
            fprintf(stdout, "ACCUMULATE pfloat8low [%d]: pfloat --> %.6e,\t float -->  %.6e, \terror = %.2f %% \n",
                    loop,
                    pfloat2float<pfloat16high>(accumulateResult_pfloat8low_pfloat),
                    accumulateResult_pfloat8low_f, percentageErrorAccumulate.get() );


        pfloat percentageErrorSumOfSquares1 =
                100.0f * ((pfloat2ieee<pfloat16high, float>(sumOfSquaresResult_upfloat8high_p) - sumOfSquaresResult_upfloat8high_f) /
                          sumOfSquaresResult_upfloat8high_f);
        if (std::abs(percentageErrorSumOfSquares1.get()) > 1.0)
            fprintf(stdout, "SUMSQARES1[%d]: pfloat --> %.6e,\t float -->  %.6e, \terror = %.2f %% \n",
                    loop,
                    pfloat2ieee<pfloat16high, float>(sumOfSquaresResult_upfloat8high_p),
                    sumOfSquaresResult_pfloat8low_f,
                    percentageErrorSumOfSquares1.get() );

        pfloat percentageErrorSumOfSquares2 =
                100.0f * ((pfloat2ieee<pfloat8low, float>(sumOfSquaresResult_pfloat8low_p) - sumOfSquaresResult_pfloat8low_f) /
                          sumOfSquaresResult_pfloat8low_f);
        if (std::abs(percentageErrorSumOfSquares2.get()) > 5.0)
            fprintf(stdout, "SUMSQARES2[%d]: pfloat --> %.6e,\t float -->  %.6e, \terror = %.2f %% \n",
                    loop,
                    pfloat2ieee<pfloat8low, float>(sumOfSquaresResult_pfloat8low_p),
                    sumOfSquaresResult_pfloat8low_f, percentageErrorSumOfSquares2.get() );

    }



    fprintf(stdout, "\n DOING CONVERSION CONSISTENCY VERIFICATION\n");
    float conv_res = 0.0;

    uint8_t run = 0xFF;
    do {
        run++;
        {
            pfloat8high pfloat_orig = run;
            conv_res = pfloat2ieee<pfloat8high, float>(pfloat_orig);
            assert(conv_res == pfloat8highTOfloat(pfloat_orig) && "pfloat8high: different conversion results");
            pfloat8high pfloat8_res = ieee2pfloat<float, pfloat8high>(conv_res);
            assert(pfloat8_res.get() == run && "pfloat8high: non consistent conversion");
        }
        {
            pfloat8low pfloat_orig = run;
            conv_res = pfloat2ieee<pfloat8low, float>(pfloat_orig);
            assert(conv_res == pfloat8lowTOfloat(pfloat_orig) && "pfloat8low: different conversion results");
            pfloat8low pfloat8_res = ieee2pfloat<float, pfloat8low>(conv_res);
            assert(pfloat8_res.get() == run && "pfloat8low: non consistent conversion");
        }
        {
            upfloat8high pfloat_orig = run;
            conv_res = pfloat2ieee<upfloat8high, float>(pfloat_orig);
            assert(conv_res == upfloat8highTOfloat(pfloat_orig) && "upfloat8high: different conversion results");
            upfloat8high pfloat8_res = ieee2pfloat<float, upfloat8high>(conv_res);
            assert(pfloat8_res.get() == run && "upfloat8high: non consistent conversion");
        }
        {
            upfloat8low pfloat_orig = run;
            conv_res = pfloat2ieee<upfloat8low, float>(pfloat_orig);
            assert(conv_res == upfloat8lowTOfloat(pfloat_orig) && "upfloat8low: different conversion results");
            upfloat8low pfloat8_res = ieee2pfloat<float, upfloat8low>(conv_res);
            assert(pfloat8_res.get() == run && "upfloat8low: non consistent conversion");
        }
    } while (run != 0xFF);

    uint16_t run16 = 0xFFFF;
    do {
        run16++;
        {
            pfloat16high pfloat_orig;
            pfloat_orig.set(run16);
            conv_res = pfloat2ieee<pfloat16high, float>(pfloat_orig);
            assert(conv_res == pfloat16highTOfloat(pfloat_orig) && "pfloat16high: different conversion results");
            pfloat16high pfloat_res = ieee2pfloat<float, pfloat16high>(conv_res);
            assert(pfloat_res.get() == run16 && "pfloat16high: non consistent conversion");
        }
        {
            pfloat16low pfloat_orig;
            pfloat_orig.set(run16);
            conv_res = pfloat2ieee<pfloat16low, float>(pfloat_orig);
            assert(conv_res == pfloat16lowTOfloat(pfloat_orig) && "pfloat16low: different conversion results");
            pfloat16low pfloat_res = ieee2pfloat<float, pfloat16low>(conv_res);
            assert(pfloat_res.get() == run16 && "pfloat16low: non consistent conversion");
        }
        {
            upfloat16high pfloat_orig;
            pfloat_orig.set(run16);
            conv_res = pfloat2ieee<upfloat16high, float>(pfloat_orig);
            assert(conv_res == upfloat16highTOfloat(pfloat_orig) && "upfloat16high: different conversion results");
            upfloat16high pfloat_res = ieee2pfloat<float, upfloat16high>(conv_res);
            assert(pfloat_res.get() == run16 && "upfloat16high: non consistent conversion");
        }
        {
            upfloat16low pfloat_orig;
            pfloat_orig.set(run16);
            conv_res = pfloat2ieee<upfloat16low, float>(pfloat_orig);
            assert(conv_res == upfloat16lowTOfloat(pfloat_orig) && "upfloat16low: different conversion results");
            upfloat16low pfloat_res = ieee2pfloat<float, upfloat16low>(conv_res);
            assert(pfloat_res.get() == run16 && "upfloat16low: non consistent conversion");
        }
        {
            pfloat16 pfloat_orig;
            pfloat_orig.set(run16);
            conv_res = pfloat2ieee<pfloat16, float>(pfloat_orig);
            pfloat16 pfloat_res = ieee2pfloat<float, pfloat16>(conv_res);
            //fprintf(stdout, "0x%x 0x%x 0x%x\n", run16, *(uint32_t*)&conv_res, pfloat_res.get());
            if ((*(uint32_t*)&conv_res & 0x7FFFFFFF) < 0x7f80000) { // don't check inf or nan
                assert(pfloat_res.get() == run16 && "pfloat16: non consistent conversion");
                assert(conv_res == pfloat16TOfloat(pfloat_orig) && "pfloat16: different conversion results");
            }
        }
    } while (run16 != 0xFFFF);
    fprintf(stdout, "Done\n\n");

    pfloat8high test_pfloat8h;



/*    pfloat8high pfloat8high_all[256] = {(uint8_t)0x00};
    pfloat8high_all[0].set(0x81) ; // -1.0
    pfloat8high_all[255].set(0x01) ; // +1.0
    fprintf(stdout, "%f (0x%0*x)\n", pfloat8highTOfloat(pfloat8high_all[0]), 2, pfloat8high_all[0]);
    for (uint8_t i = 1; i <= 126; i++) // -9.687500e-01 .. -1.862645e-09
        pfloat8high_all[i].set((uint8_t)(256 - i));
    pfloat8high_all[127].set(0x80); // -0.0
    pfloat8high_all[128].set(0x00); // +0.0
    for (uint8_t i = 129; i <= 254; i++) // -9.687500e-01 .. -1.862645e-09
        pfloat8high_all[i].set((uint8_t)(i-127));

    run = 0xFF;
    do {
        run++; // overflow to 0x00 in first iteration
        pfloat8high mypfloatresult, mypfloat = pfloat8high_all[run];
        float myconvtest = pfloat8highTOfloat(mypfloat);
        mypfloatresult = floatTOpfloat8high(myconvtest);
        fprintf(stdout, "%3d: 0x%0*x --> 0b%d%d%d%d%d%d%d%d --> %.6e --> 0x%0*x\n",
                run, 2, mypfloat,
                (mypfloat.get() & 0x80) >> 7,
                (mypfloat.get() & 0x40) >> 6,
                (mypfloat.get() & 0x20) >> 5,
                (mypfloat.get() & 0x10) >> 4,
                (mypfloat.get() & 0x08) >> 3,
                (mypfloat.get() & 0x04) >> 2,
                (mypfloat.get() & 0x02) >> 1,
                mypfloat.get() & 0x01,
                 myconvtest, 2, mypfloatresult);
        assert(mypfloat == mypfloatresult && "ERROR: Conversion comparison not consistent");
        assert(mypfloat <= mypfloatresult && "ERROR: Conversion comparison not consistent");
        assert(mypfloat >= mypfloatresult && "ERROR: Conversion comparison not consistent");
        assert(!(mypfloat > mypfloatresult) && "ERROR: Conversion comparison not consistent");
        assert(!(mypfloat < mypfloatresult) && "ERROR: Conversion comparison not consistent");
        if ((run != 0xFF) && (pfloat8high_all[run] != 0.0f)) {
            pfloat8high temp = pfloat8high_all[run+1];
            assert(!(mypfloat == temp) && "ERROR: Conversion comparison not consistent");
            assert(mypfloat <= temp && "ERROR: Conversion comparison not consistent");
            assert(!(mypfloat >= temp) && "ERROR: Conversion comparison not consistent");
            assert(!(mypfloat > temp) && "ERROR: Conversion comparison not consistent");
            assert((mypfloat < temp) && "ERROR: Conversion comparison not consistent");
        }
    } while (run != 0xFF);

     */

    fprintf(stdout, "-------------------------\n");


    return 0;
}

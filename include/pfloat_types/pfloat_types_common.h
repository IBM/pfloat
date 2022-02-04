#ifndef PFLOAT_PFLOAT_TYPES_COMMON_H
#define PFLOAT_PFLOAT_TYPES_COMMON_H

#include <cstdint>

namespace pfloat_n {


#ifndef pfloat_DefaultRoundingMethod
        #define pfloat_DefaultRoundingMethod nearest
#endif
#ifndef pfloat_DefaultFP32MantissaMask
#define pfloat_DefaultFP32MantissaMask 0xFFFFFFFFu
#endif
#ifndef pfloat_DefaultFP64MantissaMask
#define pfloat_DefaultFP64MantissaMask 0xFFFFFFFFFFFFFFFFu
#endif


    // ---------ROUNDING-------------------
    // down: round towards zero; this is the same as truncating mantissa bits
    // up: round towards magnitude 1 (if any of the bits at LSB-N are set),
    // nearest: round magnitude up if LSB-1 is one, round magnitude down if LSB-1 is zero
    // random: randomly round up or down
    // stochastic: stochastically round up or down (comparing all LSB-N bit against a 'random' value)
    enum pfloatRoundingMethod_enum {
        down, up, nearest, random, stochastic
    };

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT8HIGH aka aka PFLOAT8h aka PFLOAT8
    //

    // CLASS
    class pfloat8high; // forward declaration
    typedef pfloat8high pfloat8h; // A shortcut
    typedef pfloat8high pfloat8; // A shortcut with the assumption that pfloat8high is the 'workhorse'

    // UNDERLYING TYPE
    typedef uint8_t pfloat8high_t; // a pfloat8 figure has 8 bits
    typedef pfloat8high_t pfloat8h_t; // a shortcut
    typedef pfloat8high_t pfloat8_t; // A shortcut with the assumption that pfloat8high is the 'workhorse'
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT8LOW aka PFLOAT8L
    //
    class pfloat8low; // forward declaration
    typedef pfloat8low pfloat8l; // a shortcut
    typedef uint8_t pfloat8low_t; // a pfloat8 figure has 8 bits
    typedef pfloat8low_t pfloat8l_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       UPFLOAT8HIGH aka UPFLOAT8H aka UPFLOAT8 (unsigned pfloat8h)
    //
    class upfloat8high; // forward declaration
    typedef upfloat8high upfloat8h; // A shortcut
    typedef upfloat8high upfloat8; // A shortcut with the assumption that upfloat8high is the 'workhorse'
    typedef uint8_t upfloat8high_t; // a pfloat8 figure has 8 bits
    typedef upfloat8high_t upfloat8h_t; // a shortcut
    typedef upfloat8high_t upfloat8_t; // A shortcut with the assumption that pfloat8high is the 'workhorse'
    ///////////////////////////////////////////////////////////////////
    //
    //       UPFLOAT8LOW aka UPFLOAT8L (unsigned pfloat8l)
    //
    class upfloat8low; // forward declaration
    typedef upfloat8low upfloat8l; // A shortcut
    typedef uint8_t upfloat8low_t; // a pfloat8 figure has 8 bits
    typedef upfloat8low_t upfloat8l_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT8X
    //
    class pfloat8x; // forward declaration
    typedef uint8_t pfloat8x_t; // a pfloat8 figure has 8 bits

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16HIGH
    //
    class pfloat16high; // forward declaration
    typedef pfloat16high pfloat16h; // A shortcut
    typedef uint16_t pfloat16high_t; // a pfloat16h figure has 16 bits
    typedef pfloat16high_t pfloat16h_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16LOW
    //
    class pfloat16low; // forward declaration
    typedef pfloat16low pfloat16l; // A shortcut
    typedef uint16_t pfloat16low_t; // a pfloat16l figure has 16 bits
    typedef pfloat16low_t pfloat16l_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       UPFLOAT16HIGH
    //
    class upfloat16high; // forward declaration
    typedef upfloat16high upfloat16h; // A shortcut
    typedef uint16_t upfloat16high_t; // a upfloat16h figure has 16 bits
    typedef upfloat16high_t uupfloat16h_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       UPFLOAT16LOW
    //
    class upfloat16low; // forward declaration
    typedef upfloat16low upfloat16l; // A shortcut
    typedef uint16_t upfloat16low_t; // a upfloat16l figure has 16 bits
    typedef upfloat16low_t uupfloat16l_t; // a shortcut
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16X
    //
    class pfloat16x; // forward declaration
    typedef uint16_t pfloat16x_t; // a pfloat8 figure has 8 bits

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16
    //
    class pfloat16; // forward declaration
    typedef uint16_t pfloat16_t; // a pfloat16 figure has 16 bits
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT32
    //
    class pfloat32; // forward declaration
    typedef uint32_t pfloat32_t; // a pfloat32 figure has 32 bits
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT64
    //
    class pfloat64; // forward declaration
    typedef uint64_t pfloat64_t; // a pfloat64 figure has 64 bits

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16D
    //
    class pfloat16d; // forward declaration
    typedef uint16_t pfloat16d_t; // a pfloat16 figure has 16 bits
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT32
    //
    class pfloat32d; // forward declaration
    typedef uint32_t pfloat32d_t; // a pfloat32 figure has 32 bits
    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT64
    //
    class pfloat64d; // forward declaration
    typedef uint64_t pfloat64d_t; // a pfloat64 figure has 64 bits

    //
    //       PFLOAT (a dummy class to implement float in class form)
    //
    class pfloat; // forward declaration
    typedef float pfloat_t; // a pfloat figure has 32 bits in the form of a float
    ///////////////////////////////////////////////////////////////////
    //
    //       PDOUBLE (a dummy class to implement double in class form)
    //
    class pdouble; // forward declaration
    typedef double pdouble_t; // a pdouble figure has 64 bits in the form of a double
    ///////////////////////////////////////////////////////////////////
    //
    //       PBFLOAT (a dummy class to implement bfloat in class form)
    //
    class pbfloat; // forward declaration
    typedef uint16_t pbfloat_t; // a pbfloat figure has 16 bits in the form of a Uint16_t

    ///////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------
    // VECTORS

    // helper defines
#define pfloat_vectorType(base_t, underscore, vectorsize, _t) base_t base_t##underscore##vectorsize##_t
#define pfloat_vectorClass(base_t, underscore, vectorsize) base_t##underscore##vectorsize
#define pfloat_create_8bitVectorTypeAndClass(base_t, vectorsize) \
    typedef pfloat_vectorType(base_t, _, vectorsize, _t)[vectorsize] __attribute__((aligned(vectorsize))); \
    class pfloat_vectorClass(base_t, _, vectorsize);
#define pfloat_create_16bitVectorTypeAndClass(base_t, vectorsize) \
    typedef pfloat_vectorType(base_t, _, vectorsize, _t)[vectorsize] __attribute__((aligned((vectorsize) * 2))); \
    class pfloat_vectorClass(base_t, _, vectorsize);
#define pfloat_create_32bitVectorTypeAndClass(base_t, vectorsize) \
    typedef pfloat_vectorType(base_t, _, vectorsize, _t)[vectorsize] __attribute__((aligned((vectorsize) * 4))); \
    class pfloat_vectorClass(base_t, _, vectorsize);

    // Create vector types like 'pfloat8_64_t' for a 64 element array of pfloat8 elements (64-byte aligned), ..
    // ... plus a corresponding class forward declaration like 'pfloat8_64'
#define pfloat_create_all8bitVectorTypeAndClass(base_t) \
    pfloat_create_8bitVectorTypeAndClass(base_t, 2) \
    pfloat_create_8bitVectorTypeAndClass(base_t, 4) \
    pfloat_create_8bitVectorTypeAndClass(base_t, 8) \
    pfloat_create_8bitVectorTypeAndClass(base_t,  16) \
    pfloat_create_8bitVectorTypeAndClass(base_t, 32) \
    pfloat_create_8bitVectorTypeAndClass(base_t, 64)
#define pfloat_create_all16bitVectorTypeAndClass(base_t) \
    pfloat_create_16bitVectorTypeAndClass(base_t, 2) \
    pfloat_create_16bitVectorTypeAndClass(base_t, 4) \
    pfloat_create_16bitVectorTypeAndClass(base_t, 8) \
    pfloat_create_16bitVectorTypeAndClass(base_t,  16) \
    pfloat_create_16bitVectorTypeAndClass(base_t, 32) \
    pfloat_create_16bitVectorTypeAndClass(base_t, 64)
#define pfloat_create_all32bitVectorTypeAndClass(base_t) \
    pfloat_create_32bitVectorTypeAndClass(base_t, 2) \
    pfloat_create_32bitVectorTypeAndClass(base_t, 4) \
    pfloat_create_32bitVectorTypeAndClass(base_t, 8) \
    pfloat_create_32bitVectorTypeAndClass(base_t,  16) \
    pfloat_create_32bitVectorTypeAndClass(base_t, 32) \
    pfloat_create_32bitVectorTypeAndClass(base_t, 64)

    pfloat_create_all8bitVectorTypeAndClass(pfloat8high)
    pfloat_create_all8bitVectorTypeAndClass(pfloat8low)
    pfloat_create_all8bitVectorTypeAndClass(upfloat8high)
    pfloat_create_all8bitVectorTypeAndClass(upfloat8low)
    pfloat_create_all8bitVectorTypeAndClass(pfloat8x)
    pfloat_create_all16bitVectorTypeAndClass(pfloat16high)
    pfloat_create_all16bitVectorTypeAndClass(pfloat16low)
    pfloat_create_all16bitVectorTypeAndClass(upfloat16high)
    pfloat_create_all16bitVectorTypeAndClass(upfloat16low)
    pfloat_create_all16bitVectorTypeAndClass(pfloat16x)
    pfloat_create_all16bitVectorTypeAndClass(pfloat16)
    pfloat_create_all32bitVectorTypeAndClass(pfloat32)
    pfloat_create_all32bitVectorTypeAndClass(pfloat64)
    pfloat_create_all16bitVectorTypeAndClass(pfloat16d)
    pfloat_create_all32bitVectorTypeAndClass(pfloat32d)
    pfloat_create_all32bitVectorTypeAndClass(pfloat64d)
    pfloat_create_all32bitVectorTypeAndClass(pfloat)
    pfloat_create_all32bitVectorTypeAndClass(pdouble)
    pfloat_create_all32bitVectorTypeAndClass(pbfloat)


    ///////////////////////////////////////////////////////////////////////////////////
    // ----------------------------------------------
    // MATRIX

    // helper defines
#define pfloat_matrixType(base_t, underscore, vectorsize, x) base_t base_t##underscore##vectorsize##x##vectorsize
#define pfloat_create_matrixtype(base_t, vectorsize) \
    typedef pfloat_matrixType(base_t, _, vectorsize, x)[vectorsize][vectorsize] __attribute__((aligned((vectorsize)*(vectorsize))));

    // Create matrix types like 'pfloat8_8x8' for a 8*8=64 element array of pfloat8 type elements (64-byte aligned)
    pfloat_create_matrixtype(pfloat8, 2)
    pfloat_create_matrixtype(pfloat8, 4)
    pfloat_create_matrixtype(pfloat8, 8) //pfloat8_8x8
    // TODO: Create more matrix types

    // helper defines
#define pfloat_matrixTypeMultiple(base_t, underscore, howmany, vectorsize, x) \
    base_t##underscore##vectorsize##x##vectorsize base_t##underscore##howmany##x##vectorsize##x##vectorsize
#define pfloat_create_matrixtypeMultiple(base_t, howmany, vectorsize) \
    typedef pfloat_matrixTypeMultiple(base_t, _, howmany, vectorsize, x)[howmany] __attribute__((aligned((howmany)*(vectorsize)*(vectorsize))));

    pfloat_create_matrixtypeMultiple(pfloat8, 1, 4)
    pfloat_create_matrixtypeMultiple(pfloat8, 2, 4)
    pfloat_create_matrixtypeMultiple(pfloat8, 4, 4)
    // TODO: Create more types

} // end namespace pfloat_n

#endif //PFLOAT_PFLOAT_TYPES_COMMON_H

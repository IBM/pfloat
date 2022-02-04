#include "pfloat_types/pfloat16x.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16X
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat16x)
    pfloat_createConstructor(pfloat16x, pfloat8low)
    pfloat_createConstructor(pfloat16x, upfloat8high)
    pfloat_createConstructor(pfloat16x, upfloat8low)
    pfloat_createConstructor(pfloat16x, pfloat16high)
    pfloat_createConstructor(pfloat16x, pfloat16low)
    pfloat_createConstructor(pfloat16x, upfloat16high)
    pfloat_createConstructor(pfloat16x, upfloat16low)
    pfloat_createConstructor(pfloat16x, pfloat16)
    pfloat_createConstructor(pfloat16x, pfloat32)
    pfloat_createConstructor(pfloat16x, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat16x)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat16x)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat16x)


} // end of namespace pfloat_n


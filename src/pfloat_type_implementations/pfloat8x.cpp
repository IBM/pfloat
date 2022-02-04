#include "pfloat_types/pfloat8x.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT8X
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat8x)
    pfloat_createConstructor(pfloat8x, pfloat8low)
    pfloat_createConstructor(pfloat8x, upfloat8high)
    pfloat_createConstructor(pfloat8x, upfloat8low)
    pfloat_createConstructor(pfloat8x, pfloat16high)
    pfloat_createConstructor(pfloat8x, pfloat16low)
    pfloat_createConstructor(pfloat8x, upfloat16high)
    pfloat_createConstructor(pfloat8x, upfloat16low)
    pfloat_createConstructor(pfloat8x, pfloat16)
    pfloat_createConstructor(pfloat8x, pfloat32)
    pfloat_createConstructor(pfloat8x, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat8x)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat8x)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat8x)


} // end of namespace pfloat_n

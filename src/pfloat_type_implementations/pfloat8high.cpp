#include "pfloat_types/pfloat8high.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT8HIGH aka PFLOAT8
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat8high)
    pfloat_createConstructor(pfloat8high, pfloat8low)
    pfloat_createConstructor(pfloat8high, upfloat8high)
    pfloat_createConstructor(pfloat8high, upfloat8low)
    pfloat_createConstructor(pfloat8high, pfloat16high)
    pfloat_createConstructor(pfloat8high, pfloat16low)
    pfloat_createConstructor(pfloat8high, upfloat16high)
    pfloat_createConstructor(pfloat8high, upfloat16low)
    pfloat_createConstructor(pfloat8high, pfloat16)
    pfloat_createConstructor(pfloat8high, pfloat32)
    pfloat_createConstructor(pfloat8high, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat8high)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat8high)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat8high)


} // end of namespace pfloat8_n
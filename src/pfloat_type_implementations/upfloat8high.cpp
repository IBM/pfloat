#include "pfloat_types/upfloat8high.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       UPFLOAT8HIGH
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(upfloat8high)
    pfloat_createConstructor(upfloat8high, pfloat8high)
    pfloat_createConstructor(upfloat8high, pfloat8low)
    pfloat_createConstructor(upfloat8high, upfloat8low)
    pfloat_createConstructor(upfloat8high, pfloat16high)
    pfloat_createConstructor(upfloat8high, pfloat16low)
    pfloat_createConstructor(upfloat8high, upfloat16high)
    pfloat_createConstructor(upfloat8high, upfloat16low)
    pfloat_createConstructor(upfloat8high, pfloat16)
    pfloat_createConstructor(upfloat8high, pfloat32)
    pfloat_createConstructor(upfloat8high, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(upfloat8high)
    // Logic operators
    pfloat_createAllLogicOperatos(upfloat8high)
    // Basic binary operators
    pfloat_createAllMathOperators(upfloat8high)
} // end namespace pfloat_n
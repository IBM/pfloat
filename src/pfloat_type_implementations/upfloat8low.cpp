#include "pfloat_types/upfloat8low.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       UPFLOAT8LOW
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(upfloat8low)
    pfloat_createConstructor(upfloat8low, pfloat8high)
    pfloat_createConstructor(upfloat8low, pfloat8low)
    pfloat_createConstructor(upfloat8low, upfloat8high)
    pfloat_createConstructor(upfloat8low, pfloat16high)
    pfloat_createConstructor(upfloat8low, pfloat16low)
    pfloat_createConstructor(upfloat8low, upfloat16high)
    pfloat_createConstructor(upfloat8low, upfloat16low)
    pfloat_createConstructor(upfloat8low, pfloat16)
    pfloat_createConstructor(upfloat8low, pfloat32)
    pfloat_createConstructor(upfloat8low, pfloat)
    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(upfloat8low)
    // Logic operators
    pfloat_createAllLogicOperatos(upfloat8low)
    // Basic binary operators
    pfloat_createAllMathOperators(upfloat8low)

} // end namespace pfloat_n
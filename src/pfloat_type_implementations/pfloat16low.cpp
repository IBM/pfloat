#include "pfloat_types/pfloat16low.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       PFLOAT16HIGH
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat16low)
    pfloat_createConstructor(pfloat16low, pfloat8high)
    pfloat_createConstructor(pfloat16low, pfloat8low)
    pfloat_createConstructor(pfloat16low, upfloat8high)
    pfloat_createConstructor(pfloat16low, upfloat8low)
    pfloat_createConstructor(pfloat16low, pfloat16high)
    pfloat_createConstructor(pfloat16low, upfloat16high)
    pfloat_createConstructor(pfloat16low, upfloat16low)
    pfloat_createConstructor(pfloat16low, pfloat16)
    pfloat_createConstructor(pfloat16low, pfloat32)
    pfloat_createConstructor(pfloat16low, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat16low)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat16low)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat16low)

} // end namespace pfloat_n
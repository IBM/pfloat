#include "pfloat_types/pfloat16high.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       PFLOAT16HIGH
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat16high)
    pfloat_createConstructor(pfloat16high, pfloat8high)
    pfloat_createConstructor(pfloat16high, pfloat8low)
    pfloat_createConstructor(pfloat16high, upfloat8high)
    pfloat_createConstructor(pfloat16high, upfloat8low)
    pfloat_createConstructor(pfloat16high, pfloat16low)
    pfloat_createConstructor(pfloat16high, upfloat16high)
    pfloat_createConstructor(pfloat16high, upfloat16low)
    pfloat_createConstructor(pfloat16high, pfloat16)
    pfloat_createConstructor(pfloat16high, pfloat32)
    pfloat_createConstructor(pfloat16high, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat16high)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat16high)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat16high)

} // end namespace pfloat_n

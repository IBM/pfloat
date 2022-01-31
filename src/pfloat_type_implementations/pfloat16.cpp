#include "pfloat_types/pfloat_types.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       PFLOAT16
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat16)
    pfloat_createConstructor(pfloat16, pfloat8high)
    pfloat_createConstructor(pfloat16, pfloat8low)
    pfloat_createConstructor(pfloat16, upfloat8high)
    pfloat_createConstructor(pfloat16, upfloat8low)
    pfloat_createConstructor(pfloat16, pfloat16high)
    pfloat_createConstructor(pfloat16, pfloat16low)
    pfloat_createConstructor(pfloat16, upfloat16high)
    pfloat_createConstructor(pfloat16, upfloat16low)
    pfloat_createConstructor(pfloat16, pfloat32)
    pfloat_createConstructor(pfloat16, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat16)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat16)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat16)

} // end namespace pfloat_n

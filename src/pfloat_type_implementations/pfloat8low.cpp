#include "pfloat_types/pfloat8low.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       PFLOAT8LOW
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat8low)
    pfloat_createConstructor(pfloat8low, pfloat8high)
    pfloat_createConstructor(pfloat8low, upfloat8high)
    pfloat_createConstructor(pfloat8low, upfloat8low)
    pfloat_createConstructor(pfloat8low, pfloat16high)
    pfloat_createConstructor(pfloat8low, pfloat16low)
    pfloat_createConstructor(pfloat8low, upfloat16high)
    pfloat_createConstructor(pfloat8low, upfloat16low)
    pfloat_createConstructor(pfloat8low, pfloat16)
    pfloat_createConstructor(pfloat8low, pfloat32)
    pfloat_createConstructor(pfloat8low, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat8low)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat8low)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat8low)

} // end of namespace pfloat8low_n

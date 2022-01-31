#include "pfloat_types/pfloat32.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       PFLOAT32
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat32)
    pfloat_createConstructor(pfloat32, pfloat8high)
    pfloat_createConstructor(pfloat32, pfloat8low)
    pfloat_createConstructor(pfloat32, upfloat8high)
    pfloat_createConstructor(pfloat32, upfloat8low)
    pfloat_createConstructor(pfloat32, pfloat16high)
    pfloat_createConstructor(pfloat32, pfloat16low)
    pfloat_createConstructor(pfloat32, upfloat16high)
    pfloat_createConstructor(pfloat32, upfloat16low)
    pfloat_createConstructor(pfloat32, pfloat16)
    pfloat_createConstructor(pfloat32, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat32)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat32)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat32)

} // end namespace pfloat_n

#include "pfloat_types/pfloat16d.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT16D
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat16d)
    pfloat_createConstructor(pfloat16d, pfloat8low)
    pfloat_createConstructor(pfloat16d, upfloat8high)
    pfloat_createConstructor(pfloat16d, upfloat8low)
    pfloat_createConstructor(pfloat16d, pfloat16high)
    pfloat_createConstructor(pfloat16d, pfloat16low)
    pfloat_createConstructor(pfloat16d, upfloat16high)
    pfloat_createConstructor(pfloat16d, upfloat16low)
    pfloat_createConstructor(pfloat16d, pfloat16)
    pfloat_createConstructor(pfloat16d, pfloat32)
    pfloat_createConstructor(pfloat16d, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat16d)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat16d)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat16d)


} // end of namespace pfloat_n


#include "pfloat_types/pfloat32d.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT32D
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat32d)
    pfloat_createConstructor(pfloat32d, pfloat8low)
    pfloat_createConstructor(pfloat32d, upfloat8high)
    pfloat_createConstructor(pfloat32d, upfloat8low)
    pfloat_createConstructor(pfloat32d, pfloat16high)
    pfloat_createConstructor(pfloat32d, pfloat16low)
    pfloat_createConstructor(pfloat32d, upfloat16high)
    pfloat_createConstructor(pfloat32d, upfloat16low)
    pfloat_createConstructor(pfloat32d, pfloat16)
    pfloat_createConstructor(pfloat32d, pfloat32)
    pfloat_createConstructor(pfloat32d, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat32d)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat32d)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat32d)


} // end of namespace pfloat_n

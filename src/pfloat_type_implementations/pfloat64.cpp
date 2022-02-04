#include "pfloat_types/pfloat64.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT64
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat64)
    pfloat_createConstructor(pfloat64, pfloat8low)
    pfloat_createConstructor(pfloat64, upfloat8high)
    pfloat_createConstructor(pfloat64, upfloat8low)
    pfloat_createConstructor(pfloat64, pfloat16high)
    pfloat_createConstructor(pfloat64, pfloat16low)
    pfloat_createConstructor(pfloat64, upfloat16high)
    pfloat_createConstructor(pfloat64, upfloat16low)
    pfloat_createConstructor(pfloat64, pfloat16)
    pfloat_createConstructor(pfloat64, pfloat32)
    pfloat_createConstructor(pfloat64, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat64)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat64)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat64)


} // end of namespace pfloat_n

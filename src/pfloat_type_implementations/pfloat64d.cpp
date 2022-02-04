#include "pfloat_types/pfloat64d.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT64D
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pfloat64d)
    pfloat_createConstructor(pfloat64d, pfloat8low)
    pfloat_createConstructor(pfloat64d, upfloat8high)
    pfloat_createConstructor(pfloat64d, upfloat8low)
    pfloat_createConstructor(pfloat64d, pfloat16high)
    pfloat_createConstructor(pfloat64d, pfloat16low)
    pfloat_createConstructor(pfloat64d, upfloat16high)
    pfloat_createConstructor(pfloat64d, upfloat16low)
    pfloat_createConstructor(pfloat64d, pfloat16)
    pfloat_createConstructor(pfloat64d, pfloat32)
    pfloat_createConstructor(pfloat64d, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat64d)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat64d)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat64d)


} // end of namespace pfloat_n



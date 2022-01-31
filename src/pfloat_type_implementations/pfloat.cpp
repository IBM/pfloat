#include "pfloat_types/pfloat.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PFLOAT (a class implementation of float)
    //

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(pfloat)
    pfloat_createConstructor(pfloat, pfloat8high)
    pfloat_createConstructor(pfloat, pfloat8low)
    pfloat_createConstructor(pfloat, upfloat8high)
    pfloat_createConstructor(pfloat, upfloat8low)
    pfloat_createConstructor(pfloat, pfloat16high)
    pfloat_createConstructor(pfloat, pfloat16low)
    pfloat_createConstructor(pfloat, upfloat16high)
    pfloat_createConstructor(pfloat, upfloat16low)
    pfloat_createConstructor(pfloat, pfloat16)
    pfloat_createConstructor(pfloat, pfloat32)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pfloat)
    // Logic operators
    pfloat_createAllLogicOperatos(pfloat)
    // Basic binary operators
    pfloat_createAllMathOperators(pfloat)

} // end of namespace pfloat8_n

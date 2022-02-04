#include "pfloat_types/pdouble.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PDOUBLE (wrapper for double)
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pdouble)
    pfloat_createConstructor(pdouble, pfloat8low)
    pfloat_createConstructor(pdouble, upfloat8high)
    pfloat_createConstructor(pdouble, upfloat8low)
    pfloat_createConstructor(pdouble, pfloat16high)
    pfloat_createConstructor(pdouble, pfloat16low)
    pfloat_createConstructor(pdouble, upfloat16high)
    pfloat_createConstructor(pdouble, upfloat16low)
    pfloat_createConstructor(pdouble, pfloat16)
    pfloat_createConstructor(pdouble, pfloat32)
    pfloat_createConstructor(pdouble, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pdouble)
    // Logic operators
    pfloat_createAllLogicOperatos(pdouble)
    // Basic binary operators
    pfloat_createAllMathOperators(pdouble)


} // end of namespace pfloat_n


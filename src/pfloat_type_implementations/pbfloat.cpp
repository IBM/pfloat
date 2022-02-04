#include "pfloat_types/pbfloat.h"
#include "pfloat_math/pfloat_math_common.h"

namespace pfloat_n {

    ///////////////////////////////////////////////////////////////////
    //
    //       PBFLOAT (wrapper for bfloat aks BFLOAT aks BFLOAT16)
    //

    // ---------CONSTRUCTORS-------------------
    pfloat_createBasicConstructors(pbfloat)
    pfloat_createConstructor(pbfloat, pfloat8low)
    pfloat_createConstructor(pbfloat, upfloat8high)
    pfloat_createConstructor(pbfloat, upfloat8low)
    pfloat_createConstructor(pbfloat, pfloat16high)
    pfloat_createConstructor(pbfloat, pfloat16low)
    pfloat_createConstructor(pbfloat, upfloat16high)
    pfloat_createConstructor(pbfloat, upfloat16low)
    pfloat_createConstructor(pbfloat, pfloat16)
    pfloat_createConstructor(pbfloat, pfloat32)
    pfloat_createConstructor(pbfloat, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    pfloat_createAllEqualAssignments(pbfloat)
    // Logic operators
    pfloat_createAllLogicOperatos(pbfloat)
    // Basic binary operators
    pfloat_createAllMathOperators(pbfloat)


} // end of namespace pfloat_n

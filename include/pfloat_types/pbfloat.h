#ifndef PFLOAT_PBFLOAT_H
#define PFLOAT_PBFLOAT_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pbfloat {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pbfloat)
        pfloat_defineConstructor(pbfloat, pfloat8low)
        pfloat_defineConstructor(pbfloat, upfloat8high)
        pfloat_defineConstructor(pbfloat, upfloat8low)
        pfloat_defineConstructor(pbfloat, pfloat16high)
        pfloat_defineConstructor(pbfloat, pfloat16low)
        pfloat_defineConstructor(pbfloat, upfloat16high)
        pfloat_defineConstructor(pbfloat, upfloat16low)
        pfloat_defineConstructor(pbfloat, pfloat16)
        pfloat_defineConstructor(pbfloat, pfloat32)
        pfloat_defineConstructor(pbfloat, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pbfloat)
        // Logic operators
        pfloat_defineAllLogicOperators(pbfloat)
        // Basic binary operators
        pfloat_defineAllMathOperators(pbfloat)


        // ---------ACCESS TO VALUE-------------------
        inline uint16_t get() const {
            return this->value;
        }
        static inline pbfloat_t get(pbfloat input) {
            return input.value;
        }
        inline void set(pbfloat_t input) {
            this->value = input;
        }
        inline void set(pbfloat input) {
            this->value = input.value;
        }

    private:
        pbfloat_t value = 0x0000u;

    }; // end of class pbfloat

    // Make sure that a pfloat32d object is only 1 Byte in size
    static_assert(sizeof(pbfloat) == 2, "Size of pbfloat is NOT equal to 2 Bytes");

} // end of namespace pfloat_n

#endif //PFLOAT_PBFLOAT_H

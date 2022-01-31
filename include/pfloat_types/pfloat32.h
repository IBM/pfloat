#ifndef PFLOAT_PFLOAT32_H
#define PFLOAT_PFLOAT32_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat32 {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat32)
        pfloat_defineConstructor(pfloat32, pfloat8high)
        pfloat_defineConstructor(pfloat32, pfloat8low)
        pfloat_defineConstructor(pfloat32, upfloat8high)
        pfloat_defineConstructor(pfloat32, upfloat8low)
        pfloat_defineConstructor(pfloat32, pfloat16high)
        pfloat_defineConstructor(pfloat32, pfloat16low)
        pfloat_defineConstructor(pfloat32, upfloat16high)
        pfloat_defineConstructor(pfloat32, upfloat16low)
        pfloat_defineConstructor(pfloat32, pfloat16)
        pfloat_defineConstructor(pfloat32, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat32)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat32)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat32)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat32_t get() const {
            return this->value;
        }
        static inline pfloat32_t get(pfloat32 input) {
            return input.value;
        }
        inline void set(pfloat32_t input) {
            this->value = input;
        }
        inline void set(pfloat32 input) {
            this->value = input.value;
        }

    private:
        pfloat32_t value = 0x00000000u;

    }; // end of class pfloat32

    // Make sure that a pfloat32 object is only 4 Bytes in size
    static_assert(sizeof(pfloat32) == 4, "Size of pfloat32 is NOT equal to 4 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT32_H

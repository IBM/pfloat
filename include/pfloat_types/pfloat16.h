#ifndef PFLOAT_PFLOAT16_H
#define PFLOAT_PFLOAT16_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat16 {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat16)
        pfloat_defineConstructor(pfloat16, pfloat8high)
        pfloat_defineConstructor(pfloat16, pfloat8low)
        pfloat_defineConstructor(pfloat16, upfloat8high)
        pfloat_defineConstructor(pfloat16, upfloat8low)
        pfloat_defineConstructor(pfloat16, pfloat16high)
        pfloat_defineConstructor(pfloat16, pfloat16low)
        pfloat_defineConstructor(pfloat16, upfloat16high)
        pfloat_defineConstructor(pfloat16, upfloat16low)
        pfloat_defineConstructor(pfloat16, pfloat32)
        pfloat_defineConstructor(pfloat16, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat16)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat16)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat16)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat16_t get() const {
            return this->value;
        }
        static inline pfloat16_t get(pfloat16 input) {
            return input.value;
        }
        inline void set(pfloat16_t input) {
            this->value = input;
        }
        inline void set(pfloat16 input) {
            this->value = input.value;
        }

    private:
        pfloat16_t value = 0x0000;

    }; // end of class pfloat16

    // Make sure that a pfloat16 object is only 2 Byte in size
    static_assert(sizeof(pfloat16) == 2, "Size of pfloat16 is NOT equal to 2 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT16_H

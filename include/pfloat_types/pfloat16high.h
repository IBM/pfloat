#ifndef PFLOAT_PFLOAT16HIGH_H
#define PFLOAT_PFLOAT16HIGH_H


#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat16high {

    public:

        // ---------CONSTRUCTORS-------------------

        pfloat_defineBasicConstructors(pfloat16high)
        pfloat_defineConstructor(pfloat16high, pfloat8high)
        pfloat_defineConstructor(pfloat16high, pfloat8low)
        pfloat_defineConstructor(pfloat16high, upfloat8high)
        pfloat_defineConstructor(pfloat16high, upfloat8low)
        pfloat_defineConstructor(pfloat16high, pfloat16low)
        pfloat_defineConstructor(pfloat16high, upfloat16high)
        pfloat_defineConstructor(pfloat16high, upfloat16low)
        pfloat_defineConstructor(pfloat16high, pfloat16)
        pfloat_defineConstructor(pfloat16high, pfloat32)
        pfloat_defineConstructor(pfloat16high, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat16high)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat16high)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat16high)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat16high_t get() const {
            return this->value;
        }
        static inline pfloat16high_t get(pfloat16high input) {
            return input.value;
        }
        inline void set(pfloat16high_t input) {
            this->value = input;
        }
        inline void set(pfloat16high input) {
            this->value = input.value;
        }

    private:
        pfloat16high_t value = 0x00;

    }; // end of class pfloat16high

    // Make sure that a pfloat16high object is only 2 Byte in size
    static_assert(sizeof(pfloat16high) == 2, "Size of pfloat16high is NOT equal to 2 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT16HIGH_H

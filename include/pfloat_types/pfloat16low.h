#ifndef PFLOAT_PFLOAT16LOW_H
#define PFLOAT_PFLOAT16LOW_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat16low {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat16low)
        pfloat_defineConstructor(pfloat16low, pfloat8high)
        pfloat_defineConstructor(pfloat16low, pfloat8low)
        pfloat_defineConstructor(pfloat16low, upfloat8high)
        pfloat_defineConstructor(pfloat16low, upfloat8low)
        pfloat_defineConstructor(pfloat16low, pfloat16high)
        pfloat_defineConstructor(pfloat16low, upfloat16high)
        pfloat_defineConstructor(pfloat16low, upfloat16low)
        pfloat_defineConstructor(pfloat16low, pfloat16)
        pfloat_defineConstructor(pfloat16low, pfloat32)
        pfloat_defineConstructor(pfloat16low, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat16low)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat16low)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat16low)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat16low_t get() const {
            return this->value;
        }
        static inline pfloat16low_t get(pfloat16low input) {
            return input.value;
        }
        inline void set(pfloat16low_t input) {
            this->value = input;
        }
        inline void set(pfloat16low input) {
            this->value = input.value;
        }

    private:
        pfloat16low_t value = 0x00;

    }; // end of class pfloat16low

    // Make sure that a pfloat16low object is only 2 Byte in size
    static_assert(sizeof(pfloat16low) == 2, "Size of pfloat16low is NOT equal to 2 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT16LOW_H

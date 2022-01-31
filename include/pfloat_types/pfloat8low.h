#ifndef PFLOAT8_PFLOAT8LOW_H
#define PFLOAT8_PFLOAT8LOW_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {

    class pfloat8low {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat8low)
        pfloat_defineConstructor(pfloat8low, pfloat8high)
        pfloat_defineConstructor(pfloat8low, upfloat8high)
        pfloat_defineConstructor(pfloat8low, upfloat8low)
        pfloat_defineConstructor(pfloat8low, pfloat16high)
        pfloat_defineConstructor(pfloat8low, pfloat16low)
        pfloat_defineConstructor(pfloat8low, upfloat16high)
        pfloat_defineConstructor(pfloat8low, upfloat16low)
        pfloat_defineConstructor(pfloat8low, pfloat16)
        pfloat_defineConstructor(pfloat8low, pfloat32)
        pfloat_defineConstructor(pfloat8low, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat8low)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat8low)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat8low)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat8low_t get() const {
            return this->value;
        }
        static inline pfloat8low_t get(pfloat8low input) {
            return input.value;
        }
        inline void set(pfloat8low_t input) {
            this->value = input;
        }
        inline void set(pfloat8low input) {
            this->value = input.value;
        }

    private:
        pfloat8low_t value = 0x00;

    }; // end of class pfloat8low

    // Make sure that a pfloat8low object is only 1 Byte in size
    static_assert(sizeof(pfloat8low) == 1, "Size of pfloat8low is NOT equal to 1 Byte");



} // end of namespace pfloat8low_n

#endif //PFLOAT8_PFLOAT8LOW_H

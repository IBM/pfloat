#ifndef PFLOAT_UPFLOAT8LOW_H
#define PFLOAT_UPFLOAT8LOW_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class upfloat8low {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(upfloat8low)
        pfloat_defineConstructor(upfloat8low, pfloat8high)
        pfloat_defineConstructor(upfloat8low, pfloat8low)
        pfloat_defineConstructor(upfloat8low, upfloat8high)
        pfloat_defineConstructor(upfloat8low, pfloat16high)
        pfloat_defineConstructor(upfloat8low, pfloat16low)
        pfloat_defineConstructor(upfloat8low, upfloat16high)
        pfloat_defineConstructor(upfloat8low, upfloat16low)
        pfloat_defineConstructor(upfloat8low, pfloat16)
        pfloat_defineConstructor(upfloat8low, pfloat32)
        pfloat_defineConstructor(upfloat8low, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(upfloat8low)
        // Logic operators
        pfloat_defineAllLogicOperators(upfloat8low)
        // Basic binary operators
        pfloat_defineAllMathOperators(upfloat8low)

        // ---------ACCESS TO VALUE-------------------
        inline upfloat8low_t get() const {
            return this->value;
        }
        static inline upfloat8low_t get(upfloat8low input) {
            return input.value;
        }
        inline void set(upfloat8low_t input) {
            this->value = input;
        }
        inline void set(upfloat8low input) {
            this->value = input.value;
        }

    private:
        upfloat8low_t value = 0x00;

    }; // end of class upfloat8low

    // Make sure that a upfloat8low object is only 1 Byte in size
    static_assert(sizeof(upfloat8low) == 1, "Size of upfloat8low is NOT equal to 1 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_UPFLOAT8LOW_H

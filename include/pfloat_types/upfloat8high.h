#ifndef PFLOAT_UPFLOAT8HIGH_H
#define PFLOAT_UPFLOAT8HIGH_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class upfloat8high {

    public:
        // ---------CONSTRUCTORS-------------------

        pfloat_defineBasicConstructors(upfloat8high)
        pfloat_defineConstructor(upfloat8high, pfloat8high)
        pfloat_defineConstructor(upfloat8high, pfloat8low)
        pfloat_defineConstructor(upfloat8high, upfloat8low)
        pfloat_defineConstructor(upfloat8high, pfloat16high)
        pfloat_defineConstructor(upfloat8high, pfloat16low)
        pfloat_defineConstructor(upfloat8high, upfloat16high)
        pfloat_defineConstructor(upfloat8high, upfloat16low)
        pfloat_defineConstructor(upfloat8high, pfloat16)
        pfloat_defineConstructor(upfloat8high, pfloat32)
        pfloat_defineConstructor(upfloat8high, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(upfloat8high)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat8high)
        // Basic binary operators
        pfloat_defineAllMathOperators(upfloat8high)

        // ---------ACCESS TO VALUE-------------------
        inline upfloat8_t get() const {
            return this->value;
        }
        static inline upfloat8_t get(upfloat8 input) {
            return input.value;
        }
        inline void set(upfloat8_t input) {
            this->value = input;
        }
        inline void set(upfloat8 input) {
            this->value = input.value;
        }

    private:
        upfloat8_t value = 0x00;

    }; // end of class upfloat8high

    // Make sure that a upfloat8high object is only 1 Byte in size
    static_assert(sizeof(upfloat8high) == 1, "Size of upfloat8high is NOT equal to 1 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_UPFLOAT8HIGH_H

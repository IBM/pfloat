#ifndef PFLOAT_PFLOAT16X_H
#define PFLOAT_PFLOAT16X_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat16x {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat16x)
        pfloat_defineConstructor(pfloat16x, pfloat8low)
        pfloat_defineConstructor(pfloat16x, upfloat8high)
        pfloat_defineConstructor(pfloat16x, upfloat8low)
        pfloat_defineConstructor(pfloat16x, pfloat16high)
        pfloat_defineConstructor(pfloat16x, pfloat16low)
        pfloat_defineConstructor(pfloat16x, upfloat16high)
        pfloat_defineConstructor(pfloat16x, upfloat16low)
        pfloat_defineConstructor(pfloat16x, pfloat16)
        pfloat_defineConstructor(pfloat16x, pfloat32)
        pfloat_defineConstructor(pfloat16x, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat16x)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat16x)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat16x)


        // ---------ACCESS TO VALUE-------------------
        inline uint16_t get() const {
            return this->value;
        }
        static inline pfloat16x_t get(pfloat16x input) {
            return input.value;
        }
        inline void set(pfloat16x_t input) {
            this->value = input;
        }
        inline void set(pfloat16x input) {
            this->value = input.value;
        }

    private:
        pfloat16x_t value = 0x0000u;

    }; // end of class pfloat16x

    // Make sure that a pfloat16x object is only 1 Byte in size
    static_assert(sizeof(pfloat16x) == 2, "Size of pfloat16x is NOT equal to 2 Bytes");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT16X_H

#ifndef PFLOAT_PFLOAT8X_H
#define PFLOAT_PFLOAT8X_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat8x {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat8x)
        pfloat_defineConstructor(pfloat8x, pfloat8low)
        pfloat_defineConstructor(pfloat8x, upfloat8high)
        pfloat_defineConstructor(pfloat8x, upfloat8low)
        pfloat_defineConstructor(pfloat8x, pfloat16high)
        pfloat_defineConstructor(pfloat8x, pfloat16low)
        pfloat_defineConstructor(pfloat8x, upfloat16high)
        pfloat_defineConstructor(pfloat8x, upfloat16low)
        pfloat_defineConstructor(pfloat8x, pfloat16)
        pfloat_defineConstructor(pfloat8x, pfloat32)
        pfloat_defineConstructor(pfloat8x, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat8x)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat8x)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat8x)


        // ---------ACCESS TO VALUE-------------------
        inline uint8_t get() const {
            return this->value;
        }
        static inline pfloat8x_t get(pfloat8x input) {
            return input.value;
        }
        inline void set(pfloat8x_t input) {
            this->value = input;
        }
        inline void set(pfloat8x input) {
            this->value = input.value;
        }

    private:
        pfloat8x_t value = 0x00u;

    }; // end of class pfloat8x

    // Make sure that a pfloat8x object is only 1 Byte in size
    static_assert(sizeof(pfloat8x) == 1, "Size of pfloat8x is NOT equal to 1 Bytes");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT8X_H

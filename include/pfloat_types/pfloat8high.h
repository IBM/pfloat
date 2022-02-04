#ifndef PFLOAT8_PFLOAT8HIGH_H
#define PFLOAT8_PFLOAT8HIGH_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat8high {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat8high)
        pfloat_defineConstructor(pfloat8high, pfloat8low)
        pfloat_defineConstructor(pfloat8high, upfloat8high)
        pfloat_defineConstructor(pfloat8high, upfloat8low)
        pfloat_defineConstructor(pfloat8high, pfloat16high)
        pfloat_defineConstructor(pfloat8high, pfloat16low)
        pfloat_defineConstructor(pfloat8high, upfloat16high)
        pfloat_defineConstructor(pfloat8high, upfloat16low)
        pfloat_defineConstructor(pfloat8high, pfloat16)
        pfloat_defineConstructor(pfloat8high, pfloat32)
        pfloat_defineConstructor(pfloat8high, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat8high)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat8high)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat8high)


        // ---------ACCESS TO VALUE-------------------
        inline uint8_t get() const {
            return this->value;
        }
        static inline pfloat8high_t get(pfloat8high input) {
            return input.value;
        }
        inline void set(pfloat8high_t input) {
            this->value = input;
        }
        inline void set(pfloat8high input) {
            this->value = input.value;
        }

    private:
        pfloat8high_t value = 0x00;

    }; // end of class pfloat8high

    // Make sure that a pfloat8 object is only 1 Byte in size
    static_assert(sizeof(pfloat8) == 1, "Size of pfloat8high is NOT equal to 1 Byte");

} // end of namespace pfloat8_n

#endif // PFLOAT8_PFLOAT8HIGH_H

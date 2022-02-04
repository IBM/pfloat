#ifndef PFLOAT_PFLOAT16D_H
#define PFLOAT_PFLOAT16D_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat16d {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat16d)
        pfloat_defineConstructor(pfloat16d, pfloat8low)
        pfloat_defineConstructor(pfloat16d, upfloat8high)
        pfloat_defineConstructor(pfloat16d, upfloat8low)
        pfloat_defineConstructor(pfloat16d, pfloat16high)
        pfloat_defineConstructor(pfloat16d, pfloat16low)
        pfloat_defineConstructor(pfloat16d, upfloat16high)
        pfloat_defineConstructor(pfloat16d, upfloat16low)
        pfloat_defineConstructor(pfloat16d, pfloat16)
        pfloat_defineConstructor(pfloat16d, pfloat32)
        pfloat_defineConstructor(pfloat16d, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat16d)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat16d)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat16d)


        // ---------ACCESS TO VALUE-------------------
        inline uint16_t get() const {
            return this->value;
        }
        static inline pfloat16d_t get(pfloat16d input) {
            return input.value;
        }
        inline void set(pfloat16d_t input) {
            this->value = input;
        }
        inline void set(pfloat16d input) {
            this->value = input.value;
        }

    private:
        pfloat16d_t value = 0x0000;

    }; // end of class pfloat16d

    // Make sure that a pfloat8 object is only 1 Byte in size
    static_assert(sizeof(pfloat16d) == 2, "Size of pfloat16d is NOT equal to 2 Bytes");

} // end of namespace pfloat8_n


#endif //PFLOAT_PFLOAT16D_H

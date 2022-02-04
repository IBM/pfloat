#ifndef PFLOAT_PFLOAT32D_H
#define PFLOAT_PFLOAT32D_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat32d {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat32d)
        pfloat_defineConstructor(pfloat32d, pfloat8low)
        pfloat_defineConstructor(pfloat32d, upfloat8high)
        pfloat_defineConstructor(pfloat32d, upfloat8low)
        pfloat_defineConstructor(pfloat32d, pfloat16high)
        pfloat_defineConstructor(pfloat32d, pfloat16low)
        pfloat_defineConstructor(pfloat32d, upfloat16high)
        pfloat_defineConstructor(pfloat32d, upfloat16low)
        pfloat_defineConstructor(pfloat32d, pfloat16)
        pfloat_defineConstructor(pfloat32d, pfloat32)
        pfloat_defineConstructor(pfloat32d, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat32d)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat32d)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat32d)


        // ---------ACCESS TO VALUE-------------------
        inline uint32_t get() const {
            return this->value;
        }
        static inline pfloat32d_t get(pfloat32d input) {
            return input.value;
        }
        inline void set(pfloat32d_t input) {
            this->value = input;
        }
        inline void set(pfloat32d input) {
            this->value = input.value;
        }

    private:
        pfloat32d_t value = 0x00000000u;

    }; // end of class pfloat32d

    // Make sure that a pfloat32d object is only 1 Byte in size
    static_assert(sizeof(pfloat32d) == 4, "Size of pfloat32d is NOT equal to 4 Bytes");

} // end of namespace pfloat_n


#endif //PFLOAT_PFLOAT32D_H

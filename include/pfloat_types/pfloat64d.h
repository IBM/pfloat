#ifndef PFLOAT_PFLOAT64D_H
#define PFLOAT_PFLOAT64D_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat64d {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat64d)
        pfloat_defineConstructor(pfloat64d, pfloat8low)
        pfloat_defineConstructor(pfloat64d, upfloat8high)
        pfloat_defineConstructor(pfloat64d, upfloat8low)
        pfloat_defineConstructor(pfloat64d, pfloat16high)
        pfloat_defineConstructor(pfloat64d, pfloat16low)
        pfloat_defineConstructor(pfloat64d, upfloat16high)
        pfloat_defineConstructor(pfloat64d, upfloat16low)
        pfloat_defineConstructor(pfloat64d, pfloat16)
        pfloat_defineConstructor(pfloat64d, pfloat32)
        pfloat_defineConstructor(pfloat64d, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat64d)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat64d)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat64d)


        // ---------ACCESS TO VALUE-------------------
        inline uint64_t get() const {
            return this->value;
        }
        static inline pfloat64d_t get(pfloat64d input) {
            return input.value;
        }
        inline void set(pfloat64d_t input) {
            this->value = input;
        }
        inline void set(pfloat64d input) {
            this->value = input.value;
        }

    private:
        pfloat64d_t value = 0x0000000000000000u;

    }; // end of class pfloat64d

    // Make sure that a pfloat32d object is only 1 Byte in size
    static_assert(sizeof(pfloat64d) == 8, "Size of pfloat64d is NOT equal to 8 Bytes");

} // end of namespace pfloat_n

#endif //PFLOAT_PFLOAT64D_H

#ifndef PFLOAT_PFLOAT64_H
#define PFLOAT_PFLOAT64_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat64 {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat64)
        pfloat_defineConstructor(pfloat64, pfloat8low)
        pfloat_defineConstructor(pfloat64, upfloat8high)
        pfloat_defineConstructor(pfloat64, upfloat8low)
        pfloat_defineConstructor(pfloat64, pfloat16high)
        pfloat_defineConstructor(pfloat64, pfloat16low)
        pfloat_defineConstructor(pfloat64, upfloat16high)
        pfloat_defineConstructor(pfloat64, upfloat16low)
        pfloat_defineConstructor(pfloat64, pfloat16)
        pfloat_defineConstructor(pfloat64, pfloat32)
        pfloat_defineConstructor(pfloat64, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat64)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat64)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat64)


        // ---------ACCESS TO VALUE-------------------
        inline uint64_t get() const {
            return this->value;
        }
        static inline pfloat64_t get(pfloat64 input) {
            return input.value;
        }
        inline void set(pfloat64_t input) {
            this->value = input;
        }
        inline void set(pfloat64 input) {
            this->value = input.value;
        }

    private:
        pfloat64_t value = 0x0000000000000000u;

    }; // end of class pfloat64

    // Make sure that a pfloat8 object is only 1 Byte in size
    static_assert(sizeof(pfloat64) == 8, "Size of pfloat64 is NOT equal to 8 Bytes");

} // end of namespace pfloat8_n


#endif //PFLOAT_PFLOAT64_H

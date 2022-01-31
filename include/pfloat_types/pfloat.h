#ifndef PFLOAT_PFLOAT_CLASSDEFINITION_OF_PFLOAT_H
#define PFLOAT_PFLOAT_CLASSDEFINITION_OF_PFLOAT_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pfloat {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pfloat)
        pfloat_defineConstructor(pfloat, pfloat8high)
        pfloat_defineConstructor(pfloat, pfloat8low)
        pfloat_defineConstructor(pfloat, upfloat8high)
        pfloat_defineConstructor(pfloat, upfloat8low)
        pfloat_defineConstructor(pfloat, pfloat16high)
        pfloat_defineConstructor(pfloat, pfloat16low)
        pfloat_defineConstructor(pfloat, upfloat16high)
        pfloat_defineConstructor(pfloat, upfloat16low)
        pfloat_defineConstructor(pfloat, pfloat16)
        pfloat_defineConstructor(pfloat, pfloat32)

        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pfloat)
        // Logic operators
        pfloat_defineAllLogicOperators(pfloat)
        // Basic binary operators
        pfloat_defineAllMathOperators(pfloat)

        // ---------ACCESS TO VALUE-------------------
        inline pfloat_t get() const {
            return this->value;
        }
        static inline pfloat_t get(pfloat input) {
            return input.value;
        }
        inline void set(pfloat_t input) {
            this->value = input;
        }
        inline void set(pfloat input) {
            this->value = input.value;
        }

    private:
        float value = 0.0f;

    }; // end of class pfloat8

    // Make sure that a pfloat object is only 4 Byte in size
    static_assert(sizeof(pfloat) == 4, "Size of pfloat is NOT equal to 4 Byte");

} // end of namespace pfloat8_n


#endif //PFLOAT_PFLOAT_CLASSDEFINITION_OF_PFLOAT_H

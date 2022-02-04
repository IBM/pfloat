#ifndef PFLOAT_PDOUBLE_H
#define PFLOAT_PDOUBLE_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class pdouble {

    public:

        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(pdouble)
        pfloat_defineConstructor(pdouble, pfloat8low)
        pfloat_defineConstructor(pdouble, upfloat8high)
        pfloat_defineConstructor(pdouble, upfloat8low)
        pfloat_defineConstructor(pdouble, pfloat16high)
        pfloat_defineConstructor(pdouble, pfloat16low)
        pfloat_defineConstructor(pdouble, upfloat16high)
        pfloat_defineConstructor(pdouble, upfloat16low)
        pfloat_defineConstructor(pdouble, pfloat16)
        pfloat_defineConstructor(pdouble, pfloat32)
        pfloat_defineConstructor(pdouble, pfloat)


        // ---------OPERATORS-------------------
        // Unary operators
        pfloat_defineAllEqualAssignments(pdouble)
        // Logic operators
        pfloat_defineAllLogicOperators(pdouble)
        // Basic binary operators
        pfloat_defineAllMathOperators(pdouble)


        // ---------ACCESS TO VALUE-------------------
        inline double get() const {
            return this->value;
        }
        static inline pdouble_t get(pdouble input) {
            return input.value;
        }
        inline void set(pdouble_t input) {
            this->value = input;
        }
        inline void set(pdouble input) {
            this->value = input.value;
        }

    private:
        pdouble_t value = 0.0;

    }; // end of class pdouble

    // Make sure that a pdouble object is only 1 Byte in size
    static_assert(sizeof(pdouble) == 8, "Size of pdouble is NOT equal to 8 Bytes");

} // end of namespace pfloat_n

#endif //PFLOAT_PDOUBLE_H

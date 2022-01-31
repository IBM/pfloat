#ifndef PFLOAT_UPFLOAT16LOW_H
#define PFLOAT_UPFLOAT16LOW_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class upfloat16low {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(upfloat16low)
        pfloat_defineConstructor(upfloat16low, pfloat8high)
        pfloat_defineConstructor(upfloat16low, pfloat8low)
        pfloat_defineConstructor(upfloat16low, upfloat8high)
        pfloat_defineConstructor(upfloat16low, upfloat8low)
        pfloat_defineConstructor(upfloat16low, pfloat16high)
        pfloat_defineConstructor(upfloat16low, pfloat16low)
        pfloat_defineConstructor(upfloat16low, upfloat16high)
        pfloat_defineConstructor(upfloat16low, pfloat16)
        pfloat_defineConstructor(upfloat16low, pfloat32)
        pfloat_defineConstructor(upfloat16low, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        upfloat16low &operator=(float input);

        // Logic operators
        bool operator==(const upfloat16low &operand) const;
        bool operator>(const upfloat16low &operand) const;
        bool operator<(const upfloat16low &operand) const;
        bool operator>=(const upfloat16low &operand) const;
        bool operator<=(const upfloat16low &operand) const;

        // Basic binary operators
        upfloat16low operator+(const upfloat16low &adder) const;
        upfloat16low &operator+=(const upfloat16low &adder);
        upfloat16low operator-(const upfloat16low &subtractor) const;
        upfloat16low &operator-=(const upfloat16low &subtractor);
        upfloat16low operator*(const upfloat16low &multiplicator) const;
        upfloat16low &operator*=(const upfloat16low &multiplicator);
        upfloat16low operator/(const upfloat16low &divisor) const;
        upfloat16low &operator/=(const upfloat16low &divisor);

        // ---------ACCESS TO VALUE-------------------
        inline upfloat16low_t get() const {
            return this->value;
        }
        static inline upfloat16low_t get(upfloat16low input) {
            return input.value;
        }
        inline void set(upfloat16low_t input) {
            this->value = input;
        }
        inline void set(upfloat16low input) {
            this->value = input.value;
        }

    private:
        upfloat16low_t value = 0x00;

    }; // end of class upfloat16low

    // Make sure that a upfloat16low object is only 2 Byte in size
    static_assert(sizeof(upfloat16low) == 2, "Size of upfloat16low is NOT equal to 2 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_UPFLOAT16LOW_H

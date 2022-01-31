#ifndef PFLOAT_UPFLOAT16HIGH_H
#define PFLOAT_UPFLOAT16HIGH_H

#include "pfloat_types/pfloat_types_common.h"
#include "pfloat_types/pfloat_types_macros.h"

namespace pfloat_n {


    class upfloat16high {

    public:
        // ---------CONSTRUCTORS-------------------
        pfloat_defineBasicConstructors(upfloat16high)
        pfloat_defineConstructor(upfloat16high, pfloat8high)
        pfloat_defineConstructor(upfloat16high, pfloat8low)
        pfloat_defineConstructor(upfloat16high, upfloat8high)
        pfloat_defineConstructor(upfloat16high, upfloat8low)
        pfloat_defineConstructor(upfloat16high, pfloat16high)
        pfloat_defineConstructor(upfloat16high, pfloat16low)
        pfloat_defineConstructor(upfloat16high, upfloat16low)
        pfloat_defineConstructor(upfloat16high, pfloat16)
        pfloat_defineConstructor(upfloat16high, pfloat32)
        pfloat_defineConstructor(upfloat16high, pfloat)

        // ---------OPERATORS-------------------
        // Unary operators
        upfloat16high &operator=(float input);

        // Logic operators
        bool operator==(const upfloat16high &operand) const;
        bool operator>(const upfloat16high &operand) const;
        bool operator<(const upfloat16high &operand) const;
        bool operator>=(const upfloat16high &operand) const;
        bool operator<=(const upfloat16high &operand) const;

        // Basic binary operators
        upfloat16high operator+(const upfloat16high &adder) const;
        upfloat16high &operator+=(const upfloat16high &adder);
        upfloat16high operator-(const upfloat16high &subtractor) const;
        upfloat16high &operator-=(const upfloat16high &subtractor);
        upfloat16high operator*(const upfloat16high &multiplicator) const;
        upfloat16high &operator*=(const upfloat16high &multiplicator);
        upfloat16high operator/(const upfloat16high &divisor) const;
        upfloat16high &operator/=(const upfloat16high &divisor);

        // ---------ACCESS TO VALUE-------------------
        inline upfloat16high_t get() const {
            return this->value;
        }
        static inline upfloat16high_t get(upfloat16high input) {
            return input.value;
        }
        inline void set(upfloat16high_t input) {
            this->value = input;
        }
        inline void set(upfloat16high input) {
            this->value = input.value;
        }

    private:
        upfloat16high_t value = 0x00;

    }; // end of class upfloat16high

    // Make sure that a upfloat16high object is only 2 Byte in size
    static_assert(sizeof(upfloat16high) == 2, "Size of upfloat16high is NOT equal to 2 Byte");

} // end of namespace pfloat_n

#endif //PFLOAT_UPFLOAT16HIGH_H

#include "pfloat_types/upfloat16high.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       UPFLOAT16HIGH
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(upfloat16high)
    pfloat_createConstructor(upfloat16high, pfloat8high)
    pfloat_createConstructor(upfloat16high, pfloat8low)
    pfloat_createConstructor(upfloat16high, upfloat8high)
    pfloat_createConstructor(upfloat16high, upfloat8low)
    pfloat_createConstructor(upfloat16high, pfloat16high)
    pfloat_createConstructor(upfloat16high, pfloat16low)
    pfloat_createConstructor(upfloat16high, upfloat16low)
    pfloat_createConstructor(upfloat16high, pfloat16)
    pfloat_createConstructor(upfloat16high, pfloat32)
    pfloat_createConstructor(upfloat16high, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    upfloat16high& upfloat16high::operator=(const float input) {
        this->value = floatTOupfloat16high_t(input);
        return *this;
    }

    // Logic operators
    bool upfloat16high::operator==(const upfloat16high& operand) const {
        return this->value == operand.value;
    }
    bool upfloat16high::operator>(const upfloat16high& operand) const {
        return this->value > operand.value;
    }
    bool upfloat16high::operator<(const upfloat16high& operand) const {
        return this->value < operand.value;
    }
    bool upfloat16high::operator>=(const upfloat16high& operand) const {
        return this->value >= operand.value;
    }
    bool upfloat16high::operator<=(const upfloat16high& operand) const {
        return this->value <= operand.value;
    }


    // Basic binary operators
    upfloat16high upfloat16high::operator+(const upfloat16high& adder) const {
        float temp = upfloat16highTOfloat(this->value) + upfloat16highTOfloat(adder.value);
        return floatTOupfloat16high(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16high& upfloat16high::operator+=(const upfloat16high& adder) {
        float temp =  upfloat16highTOfloat(this->value) + upfloat16highTOfloat(adder.value);
        this->value = floatTOupfloat16high_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16high upfloat16high::operator-(const upfloat16high& subtractor) const {
        float temp = upfloat16highTOfloat(this->value) - upfloat16highTOfloat(subtractor.value);
        return floatTOupfloat16high(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16high& upfloat16high::operator-=(const upfloat16high& subtractor) {
        float temp = upfloat16highTOfloat(this->value) - upfloat16highTOfloat(subtractor.value);
        this->value = floatTOupfloat16high_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16high upfloat16high::operator*(const upfloat16high& multiplicator) const {
        float temp = upfloat16highTOfloat(this->value) * upfloat16highTOfloat(multiplicator.value);
        return floatTOupfloat16high(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16high& upfloat16high::operator*=(const upfloat16high& multiplicator) {
        float temp = upfloat16highTOfloat(this->value) * upfloat16highTOfloat(multiplicator.value);
        this->value = floatTOupfloat16high_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16high upfloat16high::operator/(const upfloat16high& divisor) const {
        float temp = upfloat16highTOfloat(this->value) / upfloat16highTOfloat(divisor.value);
        return floatTOupfloat16high(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16high& upfloat16high::operator/=(const upfloat16high& divisor) {
        float temp = upfloat16highTOfloat(this->value) / upfloat16highTOfloat(divisor.value);
        this->value = floatTOupfloat16high_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }


}

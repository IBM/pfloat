#include "pfloat_types/upfloat16low.h"
#include "pfloat_math/pfloat_math_common.h"

///////////////////////////////////////////////////////////////////
//
//       UPFLOAT16LOW
//

namespace pfloat_n {

    // ---------CONSTRUCTORS-------------------

    pfloat_createBasicConstructors(upfloat16low)
    pfloat_createConstructor(upfloat16low, pfloat8high)
    pfloat_createConstructor(upfloat16low, pfloat8low)
    pfloat_createConstructor(upfloat16low, upfloat8high)
    pfloat_createConstructor(upfloat16low, upfloat8low)
    pfloat_createConstructor(upfloat16low, pfloat16high)
    pfloat_createConstructor(upfloat16low, pfloat16low)
    pfloat_createConstructor(upfloat16low, upfloat16high)
    pfloat_createConstructor(upfloat16low, pfloat16)
    pfloat_createConstructor(upfloat16low, pfloat32)
    pfloat_createConstructor(upfloat16low, pfloat)

    // ---------OPERATORS-------------------
    // Unary operators
    upfloat16low& upfloat16low::operator=(const float input) {
        this->value = floatTOupfloat16low_t(input);
        return *this;
    }

    // Logic operators
    bool upfloat16low::operator==(const upfloat16low& operand) const {
        return this->value == operand.value;
    }
    bool upfloat16low::operator>(const upfloat16low& operand) const {
        return this->value > operand.value;
    }
    bool upfloat16low::operator<(const upfloat16low& operand) const {
        return this->value < operand.value;
    }
    bool upfloat16low::operator>=(const upfloat16low& operand) const {
        return this->value >= operand.value;
    }
    bool upfloat16low::operator<=(const upfloat16low& operand) const {
        return this->value <= operand.value;
    }


    // Basic binary operators
    upfloat16low upfloat16low::operator+(const upfloat16low& adder) const {
        float temp = upfloat16lowTOfloat(this->value) + upfloat16lowTOfloat(adder.value);
        return floatTOupfloat16low(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16low& upfloat16low::operator+=(const upfloat16low& adder) {
        float temp =  upfloat16lowTOfloat(this->value) + upfloat16lowTOfloat(adder.value);
        this->value = floatTOupfloat16low_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16low upfloat16low::operator-(const upfloat16low& subtractor) const {
        float temp = upfloat16lowTOfloat(this->value) - upfloat16lowTOfloat(subtractor.value);
        return floatTOupfloat16low(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16low& upfloat16low::operator-=(const upfloat16low& subtractor) {
        float temp = upfloat16lowTOfloat(this->value) - upfloat16lowTOfloat(subtractor.value);
        this->value = floatTOupfloat16low_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16low upfloat16low::operator*(const upfloat16low& multiplicator) const {
        float temp = upfloat16lowTOfloat(this->value) * upfloat16lowTOfloat(multiplicator.value);
        return floatTOupfloat16low(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16low& upfloat16low::operator*=(const upfloat16low& multiplicator) {
        float temp = upfloat16lowTOfloat(this->value) * upfloat16lowTOfloat(multiplicator.value);
        this->value = floatTOupfloat16low_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }
    upfloat16low upfloat16low::operator/(const upfloat16low& divisor) const {
        float temp = upfloat16lowTOfloat(this->value) / upfloat16lowTOfloat(divisor.value);
        return floatTOupfloat16low(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                 pfloat_DefaultRoundingMethod);
    }
    upfloat16low& upfloat16low::operator/=(const upfloat16low& divisor) {
        float temp = upfloat16lowTOfloat(this->value) / upfloat16lowTOfloat(divisor.value);
        this->value = floatTOupfloat16low_t(truncateMantissa(temp, pfloat_DefaultFP32MantissaMask),
                                          pfloat_DefaultRoundingMethod);
        return *this;
    }



}

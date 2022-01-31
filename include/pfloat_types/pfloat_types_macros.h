#ifndef PFLOAT_PFLOAT_TYPES_MACROS_H
#define PFLOAT_PFLOAT_TYPES_MACROS_H

#include "pfloat_conversions/pfloat_conversions_common.h"
#include "pfloat_conversions/pfloat_templated_conversions.tpp"

namespace pfloat_n {

//------------------------------------------------------
// helpers
#define pfloat_typeMacros_sourceTOtargetHelper(source, TO, target) source##TO##target
#define pfloat_typeMacros_sourceTOtarget(source, target) \
            pfloat_typeMacros_sourceTOtargetHelper(source, TO, target)
#define pfloat_typeMacros_sourceTOtarget_tHelper(source, TO, target, _t) source##TO##target##_t
#define pfloat_typeMacros_sourceTOtarget_t(source,target) \
          pfloat_typeMacros_sourceTOtarget_tHelper(source, TO, target, _t)
#define pfloat_typeMacros_TO_tHelper(base_t, _t) base_t##_t
#define pfloat_typeMacros_TO_t(base_t)  pfloat_typeMacros_TO_tHelper(base_t, _t)

//------------------------------------------------------
// constructors
#define pfloat_defineBasicConstructors(left_t) \
            left_t() = default; \
            left_t(float init); \
            left_t(double init); \
            left_t(pfloat8_t init) : value(init){};
#define pfloat_createBasicConstructors(left_t) \
            left_t::left_t(float init) {value = pfloat_typeMacros_sourceTOtarget_t(float, left_t)(init); } \
            left_t::left_t(double init) {value = pfloat_typeMacros_sourceTOtarget_t(float, left_t)((float)init); }

#define pfloat_defineConstructor(left_t, right_t) \
    left_t(right_t value);
#define pfloat_createConstructor(left_t, right_t) \
    left_t::left_t(right_t init) { \
        value = pfloat2pfloat<right_t, left_t>(init).get();}


//------------------------------------------------------
// equal assignment
#define pfloat_defineEqualAssignment(left_t, right_t) \
    left_t& operator=(right_t input);
#define pfloat_defineAllEqualAssignments(left_t) \
    pfloat_defineEqualAssignment(left_t, float) \
    pfloat_defineEqualAssignment(left_t, double) \
    pfloat_defineEqualAssignment(left_t, pfloat8high) \
    pfloat_defineEqualAssignment(left_t, pfloat8low) \
    pfloat_defineEqualAssignment(left_t, upfloat8high) \
    pfloat_defineEqualAssignment(left_t, upfloat8low) \
    pfloat_defineEqualAssignment(left_t, pfloat16high) \
    pfloat_defineEqualAssignment(left_t, pfloat16low) \
    pfloat_defineEqualAssignment(left_t, upfloat16high) \
    pfloat_defineEqualAssignment(left_t, upfloat16low) \
    pfloat_defineEqualAssignment(left_t, pfloat16) \
    pfloat_defineEqualAssignment(left_t, pfloat32) \
    pfloat_defineEqualAssignment(left_t, pfloat)

#define pfloat_createEqualAssignment(left_t, right_t) \
    left_t& left_t::operator=(const right_t input) {        \
        this->value = pfloat2pfloat<right_t, left_t>(input).get();\
        return *this;}
#define pfloat_createAllEqualAssignments(left_t) \
    left_t& left_t::operator=(const float input) { \
        this->value = floatTO##left_t(input).get(); \
        return *this; \
    }                                            \
    left_t& left_t::operator=(const double input) { \
        this->value = floatTO##left_t((float)input).get(); \
        return *this; \
    }                                            \
    pfloat_createEqualAssignment(left_t, pfloat8high) \
    pfloat_createEqualAssignment(left_t, pfloat8low) \
    pfloat_createEqualAssignment(left_t, upfloat8high) \
    pfloat_createEqualAssignment(left_t, upfloat8low) \
    pfloat_createEqualAssignment(left_t, pfloat16high) \
    pfloat_createEqualAssignment(left_t, pfloat16low) \
    pfloat_createEqualAssignment(left_t, upfloat16high) \
    pfloat_createEqualAssignment(left_t, upfloat16low) \
    pfloat_createEqualAssignment(left_t, pfloat16) \
    pfloat_createEqualAssignment(left_t, pfloat32) \
    pfloat_createEqualAssignment(left_t, pfloat)

//------------------------------------------------------
// math operators

// math operator simple (+, -, *, /)
#define pfloat_defineMathOperator(left_t, right_t, operator_t) \
    left_t operator operator_t (const right_t & operand);
#define pfloat_createMathOperator(left_t, right_t, operator_t) \
    left_t left_t::operator operator_t (const right_t & operand) { \
    float temp = pfloat_typeMacros_sourceTOtarget(left_t,float)(*this) \
    operator_t \
    pfloat_typeMacros_sourceTOtarget(right_t, float)(operand); \
    return pfloat_typeMacros_sourceTOtarget(float, left_t)             \
    (truncateMantissa(temp, pfloat_DefaultFP32MantissaMask), pfloat_DefaultRoundingMethod);     \
    };

// math operator including assignment (+=, -=, *=, /=)
#define pfloat_defineMathOperatorEqual(left_t, right_t, operator_t, operator_tequal) \
    left_t& operator operator_tequal (const right_t & operand);
#define pfloat_createMathOperatorEqual(left_t, right_t, operator_t, operator_tequal) \
    left_t& left_t::operator operator_tequal (const right_t & operand) { \
        float temp =  pfloat_typeMacros_sourceTOtarget(left_t, float)(*this)  operator_t \
        pfloat_typeMacros_sourceTOtarget(right_t,float)(operand); \
        this->value = pfloat_typeMacros_sourceTOtarget(float, left_t) \
        (truncateMantissa(temp, pfloat_DefaultFP32MantissaMask), pfloat_DefaultRoundingMethod).get(); \
        return *this; \
    };

#define pfloat_createMathOperators(base_t, operand_t) \
    pfloat_createMathOperator(base_t, operand_t, +) \
    pfloat_createMathOperator(base_t, operand_t, -) \
    pfloat_createMathOperator(base_t, operand_t, *) \
    pfloat_createMathOperator(base_t, operand_t, /)
#define pfloat_createMathOperatorsEqual(base_t, operand_t) \
    pfloat_createMathOperatorEqual(base_t, operand_t, +, +=) \
    pfloat_createMathOperatorEqual(base_t, operand_t, -, -=) \
    pfloat_createMathOperatorEqual(base_t, operand_t, *, *=) \
    pfloat_createMathOperatorEqual(base_t, operand_t, /, /=)

#define pfloat_createMathOperatorSet(base_t, operand_t) \
    pfloat_createMathOperators(base_t, operand_t) \
    pfloat_createMathOperatorsEqual(base_t, operand_t)

#define pfloat_createAllMathOperators(base_t) \
    pfloat_createMathOperatorSet(base_t, pfloat8high) \
    pfloat_createMathOperatorSet(base_t, pfloat8low) \
    pfloat_createMathOperatorSet(base_t, upfloat8high) \
    pfloat_createMathOperatorSet(base_t, upfloat8low) \
    pfloat_createMathOperatorSet(base_t, pfloat16high) \
    pfloat_createMathOperatorSet(base_t, pfloat16low) \
    pfloat_createMathOperatorSet(base_t, upfloat16high) \
    pfloat_createMathOperatorSet(base_t, upfloat16low) \
    pfloat_createMathOperatorSet(base_t, pfloat16) \
    pfloat_createMathOperatorSet(base_t, pfloat32) \
    pfloat_createMathOperatorSet(base_t, pfloat) \
    pfloat_createMathOperatorSet(base_t, float)

#define pfloat_defineMathOperators(base_t, operand_t) \
    pfloat_defineMathOperator(base_t, operand_t, +) \
    pfloat_defineMathOperator(base_t, operand_t, -) \
    pfloat_defineMathOperator(base_t, operand_t, *) \
    pfloat_defineMathOperator(base_t, operand_t, /)
#define pfloat_defineMathOperatorsEqual(base_t, operand_t) \
    pfloat_defineMathOperatorEqual(base_t, operand_t, +, +=) \
    pfloat_defineMathOperatorEqual(base_t, operand_t, -, -=) \
    pfloat_defineMathOperatorEqual(base_t, operand_t, *, *=) \
    pfloat_defineMathOperatorEqual(base_t, operand_t, /, /=)

#define pfloat_defineOperators(base_t, operand_t) \
    pfloat_defineMathOperators(base_t, operand_t) \
    pfloat_defineMathOperatorsEqual(base_t, operand_t)

#define pfloat_defineAllMathOperators(base_t) \
    pfloat_defineOperators(base_t, pfloat8high) \
    pfloat_defineOperators(base_t, pfloat8low) \
    pfloat_defineOperators(base_t, upfloat8high) \
    pfloat_defineOperators(base_t, upfloat8low) \
    pfloat_defineOperators(base_t, pfloat16high) \
    pfloat_defineOperators(base_t, pfloat16low) \
    pfloat_defineOperators(base_t, upfloat16high) \
    pfloat_defineOperators(base_t, upfloat16low) \
    pfloat_defineOperators(base_t, pfloat16) \
    pfloat_defineOperators(base_t, pfloat32) \
    pfloat_defineOperators(base_t, pfloat) \
    pfloat_defineOperators(base_t, float)

//------------------------------------------------------
// logic operators
#define pfloat_defineLogicOperator(operator_t, right_t) \
    bool operator operator_t(const right_t& operand) const;
#define pfloat_defineLogicOperators(right_t) \
        pfloat_defineLogicOperator(==, right_t) \
        pfloat_defineLogicOperator(!=, right_t) \
        pfloat_defineLogicOperator(>=, right_t) \
        pfloat_defineLogicOperator(<=, right_t) \
        pfloat_defineLogicOperator(>, right_t) \
        pfloat_defineLogicOperator(<, right_t)
#define pfloat_defineAllLogicOperators(dummy) \
        pfloat_defineLogicOperators(pfloat8high) \
        pfloat_defineLogicOperators(pfloat8low) \
        pfloat_defineLogicOperators(upfloat8high) \
        pfloat_defineLogicOperators(upfloat8low) \
        pfloat_defineLogicOperators(pfloat16high) \
        pfloat_defineLogicOperators(pfloat16low) \
        pfloat_defineLogicOperators(upfloat16high) \
        pfloat_defineLogicOperators(upfloat16low) \
        pfloat_defineLogicOperators(pfloat16) \
        pfloat_defineLogicOperators(pfloat32) \
        pfloat_defineLogicOperators(pfloat) \
        pfloat_defineLogicOperators(float)

#define pfloat_createLogicOperator(left_t, operator_t, right_t) \
    bool left_t::operator operator_t(const right_t& operand) const { \
        return  pfloat_typeMacros_sourceTOtarget(left_t, float)(*this) operator_t \
                pfloat_typeMacros_sourceTOtarget(right_t, float)(operand);   \
    }
#define pfloat_createLogicOperators(left_t, right_t) \
    pfloat_createLogicOperator(left_t, ==, right_t) \
    pfloat_createLogicOperator(left_t, !=, right_t) \
    pfloat_createLogicOperator(left_t, >=, right_t) \
    pfloat_createLogicOperator(left_t, <=, right_t) \
    pfloat_createLogicOperator(left_t, >, right_t) \
    pfloat_createLogicOperator(left_t, <, right_t)
#define pfloat_createAllLogicOperatos(left_t) \
    pfloat_createLogicOperators(left_t, pfloat8high) \
    pfloat_createLogicOperators(left_t, pfloat8low) \
    pfloat_createLogicOperators(left_t, upfloat8high) \
    pfloat_createLogicOperators(left_t, upfloat8low) \
    pfloat_createLogicOperators(left_t, pfloat16high) \
    pfloat_createLogicOperators(left_t, pfloat16low) \
    pfloat_createLogicOperators(left_t, upfloat16high) \
    pfloat_createLogicOperators(left_t, upfloat16low) \
    pfloat_createLogicOperators(left_t, pfloat16) \
    pfloat_createLogicOperators(left_t, pfloat32) \
    pfloat_createLogicOperators(left_t, pfloat) \
    pfloat_createLogicOperators(left_t, float)



} // end namespace pfloat_n


#endif //PFLOAT_PFLOAT_TYPES_MACROS_H

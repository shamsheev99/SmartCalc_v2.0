#include "model_object.h"

namespace s21 {

Element::Element()
    : value_(0), priority_(NUM), type_obj_(NUMBERS), sign_('\0') {}

Element::Element(double value)
    : value_(value), priority_(NUM), type_obj_(NUMBERS), sign_('\0') {}

Element::Element(char sign) : value_(0), sign_(sign) {
  if (sign == '+' || sign == '-') {
    priority_ = PLUS_MINUS;
    type_obj_ = OPERATORS;
  } else if (sign == '*' || sign == '/' || sign == '%' || sign == '^') {
    priority_ = MUL_DIV_MOD;
    type_obj_ = OPERATORS;
  } else if (sign != '(' && sign != ')') {
    priority_ = FOO;
    type_obj_ = FUNCTIONS;
  } else if (sign == '(' || sign == ')') {
    priority_ = BRACE;
    type_obj_ = BRACES;
  }
}

Element::Element(char sign, double value) : value_(value), sign_(sign) {
  priority_ = NUM;
  type_obj_ = VARIABLE;
}

Element::Element(char sign, int flag_unary) : value_(0) {
  if (flag_unary == true) {
    if (sign == '#' || sign == '~') {
      sign_ = sign;
      priority_ = UNAR;
      type_obj_ = UNARY;
    }
  }
}

bool Element::is_num() { return type_obj_ == NUMBERS && sign_ == '\0'; }

bool Element::is_foo() { return type_obj_ == FUNCTIONS; }

bool Element::is_operator() { return type_obj_ == OPERATORS; }

bool Element::is_brace() { return (type_obj_ == BRACES); }

bool Element::is_open_brace() { return (type_obj_ == BRACES && sign_ == '('); }

bool Element::is_variable() { return type_obj_ == VARIABLE; }

bool Element::is_unary() { return type_obj_ == UNARY; }

int Element::get_priority() { return priority_; }

int Element::get_type_obj() { return type_obj_; }

double Element::get_value() { return value_; }

char Element::get_sign() { return sign_; }

void Element::set_value(double value) { value_ = value; }

}  // namespace s21

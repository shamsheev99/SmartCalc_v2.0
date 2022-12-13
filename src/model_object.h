#pragma once
#include <iostream>

namespace s21 {

class Element {
 private:
  enum PRIORITY { BRACE = -1, NUM, PLUS_MINUS, MUL_DIV_MOD, UNAR, FOO };
  enum TYPE_OBJ { NUMBERS = 0, OPERATORS, FUNCTIONS, BRACES, VARIABLE, UNARY };

 private:
  double value_;
  int priority_;
  int type_obj_;
  char sign_;

 public:
  Element();
  explicit Element(double value);
  explicit Element(char sign);
  Element(char sign, double value);
  Element(char sign, int flag_unary);

 public:
  bool is_num();
  bool is_foo();
  bool is_operator();
  bool is_brace();
  bool is_open_brace();
  bool is_variable();
  bool is_unary();

 public:
  int get_priority();
  int get_type_obj();
  double get_value();
  char get_sign();
  void set_value(double value);
};

}  // namespace s21

// #endif //  _OBJECTS_MODEL_H_

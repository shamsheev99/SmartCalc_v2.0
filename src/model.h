#pragma once
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "model_object.h"

namespace s21 {

class Model {
 private:
  std::vector<Element> list_;
  std::list<Element> polish_;
  bool flag_unary_;
  std::string num_;
  unsigned int count_dot;

 private:
  void add_unary(char sign);
  void add_element(char sign);
  void add_num(double value);
  double pop_unary_ops(std::list<Element> &current);
  std::pair<double, double> pop_binary_ops(std::list<Element> &current);
  bool check_operators(char sign);
  void from_list_to_list(std::list<Element> &input, std::list<Element> &output);
  void from_list_to_list_front(std::list<Element> &input,
                               std::list<Element> &output);

 public:
  Model();

 public:
  std::vector<Element> &get_vector();
  std::list<Element> &get_list();
  std::list<Element> &get_list_other();

 public:
  void inf_to_polish();
  double calc_polish();

 public:
  void add_number(const std::string &input_str);
  void add_number(double value);
  void add_operator(std::string str);
  void add_function(const std::string &foo);
  void add_variable(double value);

 public:
  void set_value_x(double value);
  void clear();
};

}  // namespace s21

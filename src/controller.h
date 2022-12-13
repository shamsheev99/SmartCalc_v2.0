#pragma once
#include "model.h"

namespace s21 {
class Controller {
 private:
  Model calc_;

 public:
  Controller();

 public:
  Model &get_model();
  void set_model(Model const &model);

 public:
  bool add_number(const std::string &input_str);
  void add_number(double value);
  bool add_operator(std::string str);
  bool add_function(const std::string &str);
  void add_variable(double value);
  void add_exp();

 public:
  void polish_notation();
  std::pair<double, bool> calc_notation();

 public:
  void set_x(double value);
  void fix_result(std::string result);
  bool empty();
  void clear();
};
}  // namespace s21
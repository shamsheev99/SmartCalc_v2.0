#include "controller.h"

namespace s21 {

Controller::Controller() {}

bool Controller::add_number(const std::string &input_str) {
  try {
    calc_.add_number(input_str);
    return false;
  } catch (const std::exception &e) {
    return true;
  }
}

void Controller::add_number(double value) { calc_.add_number(value); }

bool Controller::add_operator(std::string str) {
  try {
    calc_.add_operator(str);
    return false;
  } catch (const std::exception &e) {
    return true;
  }
}

bool Controller::add_function(const std::string &str) {
  try {
    calc_.add_function(str);
    return false;

  } catch (const std::exception &e) {
    return true;
  }
}

void Controller::add_variable(double value) { calc_.add_variable(value); }

void Controller::add_exp() {
  this->add_operator("*");
  this->add_number(10);
  this->add_operator("^");
}

void Controller::polish_notation() {
  if (!calc_.get_vector().empty()) calc_.inf_to_polish();
}

std::pair<double, bool> Controller::calc_notation() {
  if (calc_.get_list().empty()) return {0, false};
  try {
    return {calc_.calc_polish(), false};
  } catch (const std::exception &e) {
    return {0, true};
  }
}
void Controller::clear() { calc_.clear(); }

void Controller::set_x(double value) { calc_.set_value_x(value); }

void Controller::fix_result(std::string result) {
  calc_.clear();
  calc_.add_number(result);
}

bool Controller::empty() {
  if (calc_.get_list().empty() && calc_.get_vector().empty())
    return true;
  else
    return false;
}

Model &Controller::get_model() { return calc_; }

void Controller::set_model(Model const &other) { this->calc_ = other; }

}  // namespace s21

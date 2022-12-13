#include "credit_controller.h"

s21::CreditController::CreditController() {}

void s21::CreditController::set_period(int month) { model_.set_period(month); }

void s21::CreditController::set_period(int years, int month) {
  model_.set_period(years, month);
}

void s21::CreditController::set_sum(double sum) { model_.set_sum(sum); }

void s21::CreditController::set_percent(double percent) {
  model_.set_percent(percent);
}

std::vector<std::pair<double, double>> s21::CreditController::get_pays() {
  return model_.get_pays();
}

double s21::CreditController::get_overpay() { return model_.get_overpay(); }

double s21::CreditController::get_full_pay() { return model_.get_full_pay(); }

void s21::CreditController::calc_annuity() {
  model_.set_type(ANNUITY);
  model_.calc_credit();
}

void s21::CreditController::calc_different() {
  model_.set_type(DIFFERENTIATED);
  model_.calc_credit();
}

std::vector<double> s21::CreditController::get_current_sum() {
  return model_.get_current_sum();
}

void s21::CreditController::clear() { model_.clear(); }

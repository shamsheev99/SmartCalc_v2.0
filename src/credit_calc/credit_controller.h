#pragma once
#include "credit_model.h"

namespace s21 {

class CreditController {
private:
  enum TYPE { ANNUITY, DIFFERENTIATED };

private:
  CreditModel model_;

public:
  CreditController();

public:
  void calc_annuity();
  void calc_different();

public:
  void set_period(int month);
  void set_period(int years, int month);
  void set_sum(double sum);
  void set_percent(double percent);

public:
  std::vector<std::pair<double, double>> get_pays();
  std::vector<double> get_current_sum();
  double get_overpay();
  double get_full_pay();

public:
  void clear();
};

} // namespace s21
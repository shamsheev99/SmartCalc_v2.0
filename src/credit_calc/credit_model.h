#pragma once
#include <cmath>
#include <iostream>
#include <vector>

namespace s21 {

class CreditModel {
private:
  enum TYPE { ANNUITY, DIFFERENTIATED };

private:
  double sum_;
  double percent_;
  bool type_;
  int period_;

private:
  std::vector<std::pair<double, double>> pays_;
  std::vector<double> current_sum_;
  double full_pay_;
  double overpay_;

private:
  void calc_annuity();
  void calc_differnt();

public:
  CreditModel();

public:
  void calc_credit();

public:
  void set_sum(double sum);
  void set_percent(double percent);
  void set_type(bool type);
  void set_period(int period);
  void set_period(int years, int months);

public:
  std::vector<std::pair<double, double>> get_pays();
  double get_overpay();
  double get_full_pay();
  std::vector<double> get_current_sum();

public:
  void clear();
};

} // namespace s21

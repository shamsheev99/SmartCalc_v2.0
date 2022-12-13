#include "credit_model.h"

s21::CreditModel::CreditModel()
    : sum_(0), percent_(0), type_(ANNUITY), period_(0), full_pay_(0),
      overpay_(0) {}

void s21::CreditModel::calc_credit() {
  if (type_ == ANNUITY)
    calc_annuity();
  else
    calc_differnt();
  overpay_ = full_pay_ - sum_;
}

void s21::CreditModel::calc_annuity() {
  double tmp_sum = sum_;
  double month_percent = percent_ / 12.0 / 100;
  double k_annuity = (month_percent * pow((1 + month_percent), period_)) /
                     (pow((1 + month_percent), period_) - 1);
  std::cout << "koeff - " << k_annuity << std::endl;
  double month_pay = k_annuity * sum_;
  for (int i = 0; i < period_; i++) {
    double month_percent_pay = tmp_sum * month_percent;
    pays_.push_back({month_pay - month_percent_pay, month_percent_pay});
    full_pay_ += month_pay;
    tmp_sum -= month_pay - month_percent_pay;
    current_sum_.push_back(tmp_sum);
  }
}

void s21::CreditModel::calc_differnt() {
  double tmp_sum = sum_;
  double month_percent = percent_ / 12.0 / 100;
  double pay_credit_body = sum_ / period_;
  for (int i = 0; i < period_; i++) {
    pays_.push_back(
        {pay_credit_body, (sum_ - pay_credit_body * i) * month_percent});
    full_pay_ += (pays_[i].first + pays_[i].second);
    tmp_sum -= pay_credit_body;
    current_sum_.push_back(tmp_sum);
  }
}

void s21::CreditModel::set_sum(double sum) { sum_ = sum; }

void s21::CreditModel::set_percent(double percent) { percent_ = percent; }

void s21::CreditModel::set_type(bool type) { type_ = type; }

void s21::CreditModel::set_period(int period) { period_ = period; }

void s21::CreditModel::set_period(int years, int months) {
  set_period(years * 12 + months);
}

std::vector<std::pair<double, double>> s21::CreditModel::get_pays() {
  return pays_;
}
double s21::CreditModel::get_overpay() { return overpay_; }

double s21::CreditModel::get_full_pay() { return full_pay_; }

std::vector<double> s21::CreditModel::get_current_sum() { return current_sum_; }

void s21::CreditModel::clear() {
  sum_ = 0;
  percent_ = 0;
  type_ = 0;
  period_ = 0;
  pays_.clear();
  current_sum_.clear();
  full_pay_ = 0;
  overpay_ = 0;
}

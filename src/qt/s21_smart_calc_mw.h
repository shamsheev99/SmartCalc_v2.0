#ifndef S21_SMART_CALC_MW_H
#define S21_SMART_CALC_MW_H

#include <QMainWindow>

#include "../controller.h"
#include "credit_calc.h"
#include "s21_plot_print.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_smart_calc_MW;
}
QT_END_NAMESPACE

class s21_smart_calc_MW : public QMainWindow {
  Q_OBJECT
 public:
  s21_smart_calc_MW(QWidget *parent = nullptr);
  ~s21_smart_calc_MW();

 private slots:
  void on_pushButton_ans_clicked();

 private:
  Ui::s21_smart_calc_MW *ui;
  s21_plot_print *plot_window;
  credit_calc *credit_window;
  s21::Controller calc_;
 private slots:
  void key_numbers();
  void key_operations();
  void key_functions();
  void var_operations();
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_exp_clicked();
  bool error(bool expr);

 signals:
  void signal(s21::Controller calc);
};
#endif  // S21_SMART_CALC_MW_H

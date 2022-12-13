#ifndef S21_PLOT_PRINT_H
#define S21_PLOT_PRINT_H

#include <QDialog>

#include "../controller.h"
#include "QVector"

namespace Ui {
class s21_plot_print;
}

class s21_plot_print : public QDialog {
  Q_OBJECT

 public:
  explicit s21_plot_print(QWidget *parent = nullptr);
  ~s21_plot_print();

 private:
  Ui::s21_plot_print *ui;
  s21::Controller calc_;
  void calc_graph(double minX, double maxX, double minY, double maxY);
 public slots:
  void slot(s21::Controller calc);
 private slots:
  void on_pushButton_resize_clicked();
};

#endif  // S21_PLOT_PRINT_H

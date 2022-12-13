#include "s21_plot_print.h"
#include "../controller.h"
#include "ui_s21_plot_print.h"

s21_plot_print::s21_plot_print(QWidget *parent)
    : QDialog(parent), ui(new Ui::s21_plot_print) {
  ui->setupUi(this);
}

s21_plot_print::~s21_plot_print() { delete ui; }

void s21_plot_print::calc_graph(double minX, double maxX, double minY,
                                double maxY) {
  QVector<double> x, y;
  double X = minX;
  double step = (maxX - minX) / 100000;
  double min = 1000000;
  double max = -10000000;
  double scale_k_y_max = 1.005;
  double scale_k_y_min = 0.995;
  double scale_k_x = 1.005;
  const double limit = 1000000;
  while (X < maxX) {
    x.push_back(X);
    calc_.set_x(X);
    std::pair<double, bool> result = calc_.calc_notation();
    if (result.second == true) {
      ui->label->setText("ERROR");
      break;
    }
    y.push_back(result.first);
    if (min > result.first && !isinf(result.first))
      min = result.first;
    if (max < result.first && !isinf(result.first))
      max = result.first;
    X += step;
  }
  if (min < 0) {
    scale_k_y_min = 1.005;
  }
  if (max < 0) {
    scale_k_y_max = 0.995;
  }
  if (min < -1 * limit)
    min = -1 * limit;
  if (max > limit)
    max = limit;
  ui->widget->xAxis->setRange(minX * scale_k_x, maxX * scale_k_x);
  if (ui->checkBox_autoscale->isChecked()) {
    ui->widget->yAxis->setRange(min * scale_k_y_min, max * scale_k_y_max);
    ui->doubleSpinBox_maxY->setValue(max * scale_k_y_max);
    ui->doubleSpinBox_minY->setValue(min * scale_k_y_min);
  } else {
    ui->doubleSpinBox_maxY->update();
    ui->doubleSpinBox_minY->update();
    ui->widget->yAxis->setRange(minY * scale_k_y_min, maxY * scale_k_y_max);
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
  ui->widget->replot();
}

void s21_plot_print::slot(s21::Controller calc) {
  calc_.set_model(calc.get_model());
  calc_graph(-M_PI, M_PI, -5, 5);
  ui->doubleSpinBox_maxX->setValue(M_PI * 1.005);
  ui->doubleSpinBox_minX->setValue(-M_PI * 1.005);
}

void s21_plot_print::on_pushButton_resize_clicked() {
  if (ui->doubleSpinBox_minX->value() >= ui->doubleSpinBox_maxX->value() ||
      (ui->doubleSpinBox_minY->value() >= ui->doubleSpinBox_maxY->value() &&
       !ui->checkBox_autoscale->isChecked())) {
    ui->label->setText("ERROR");
  } else {
    ui->widget->removeGraph(0);
    qDebug("hihi");
    calc_graph(ui->doubleSpinBox_minX->value(), ui->doubleSpinBox_maxX->value(),
               ui->doubleSpinBox_minY->value(),
               ui->doubleSpinBox_maxY->value());
  }
}

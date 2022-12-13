#include "credit_calc.h"
#include "../credit_calc/credit_controller.h"
#include "ui_credit_calc.h"
#include <vector>

credit_calc::credit_calc(QWidget *parent)
    : QDialog(parent), ui(new Ui::credit_calc) {
  ui->setupUi(this);
}

credit_calc::~credit_calc() { delete ui; }

void credit_calc::add_table(QStandardItemModel &model, double pay, int i,
                            int j) {
  QStandardItem *item = new QStandardItem(QString::number(pay, 'f', 2));
  model.setItem(i, j, item);
}

void credit_calc::on_pushButton_calculate_clicked() {
  credit.clear();
  credit.set_percent(ui->doubleSpinBox_bid->value());
  credit.set_period(ui->spinBox_term->value());
  credit.set_sum(ui->doubleSpinBox_credit_sum->value());
  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels =
      QObject::tr("Сумма платежа;Платеж по основному долгу;Платеж "
                  "по процентам;Остаток долга")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);
  if (ui->radioButton_annuity->isChecked()) {
    credit.calc_annuity();
    for (int i = 0; i < ui->spinBox_term->value(); i++) {
      add_table(*model,
                credit.get_pays()[i].first + credit.get_pays()[i].second, i, 0);
      add_table(*model, credit.get_pays()[i].first, i, 1);
      add_table(*model, credit.get_pays()[i].second, i, 2);
      add_table(*model, credit.get_current_sum()[i], i, 3);
    }
  }
  if (ui->radioButton_different->isChecked()) {
    credit.calc_different();
    for (int i = 0; i < ui->spinBox_term->value(); i++) {
      add_table(*model,
                credit.get_pays()[i].first + credit.get_pays()[i].second, i, 0);
      add_table(*model, credit.get_pays()[i].first, i, 1);
      add_table(*model, credit.get_pays()[i].second, i, 2);
      add_table(*model, credit.get_current_sum()[i], i, 3);
    }
  }
  ui->lineEdit_overpayment->setText(
      QString::number(credit.get_overpay(), 'f', 2));
  ui->lineEdit_total->setText(QString::number(credit.get_full_pay(), 'f', 2));

  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

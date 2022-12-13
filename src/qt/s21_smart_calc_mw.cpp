#include "s21_smart_calc_mw.h"
#include "../controller.h"
#include "QMessageBox"
#include "QString"
#include "ui_s21_smart_calc_mw.h"

s21_smart_calc_MW::s21_smart_calc_MW(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_smart_calc_MW) {
  ui->setupUi(this);
  connect(ui->pushButton_num0, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num1, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num2, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num3, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num4, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num5, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num6, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num7, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num8, SIGNAL(clicked()), this, SLOT(key_numbers()));
  connect(ui->pushButton_num9, SIGNAL(clicked()), this, SLOT(key_numbers()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(key_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(key_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(key_operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(key_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(key_operations()));
  connect(ui->pushButton_braceO, SIGNAL(clicked()), this,
          SLOT(key_operations()));
  connect(ui->pushButton_braceC, SIGNAL(clicked()), this,
          SLOT(key_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(key_operations()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(var_operations()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(key_functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(key_functions()));
}

s21_smart_calc_MW::~s21_smart_calc_MW() { delete ui; }

bool s21_smart_calc_MW::error(bool expr) {
  if (expr == true) {
    ui->label->setText("ERROR");
    ui->statusbar->showMessage("Error", 1000);
    calc_.clear();
    return false;
  } else {
    return true;
  }
}

void s21_smart_calc_MW::on_pushButton_ans_clicked() {
  calc_.polish_notation();
  if (ui->radioButton->isChecked() == true) {
    plot_window = new s21_plot_print(this);
    connect(this, &s21_smart_calc_MW::signal, plot_window,
            &s21_plot_print::slot);
    emit signal(calc_);
    plot_window->setModal(true);
    plot_window->exec();
  }
  std::pair<double, bool> res = calc_.calc_notation();
  if (error(res.second)) {
    ui->label->setText(QString::number(res.first, 'g'));
    calc_.fix_result(ui->label->text().toStdString());
  }
}

void s21_smart_calc_MW::key_numbers() {
  QPushButton *key = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + key->text());
  error(calc_.add_number(key->text().toStdString()));
}

void s21_smart_calc_MW::key_operations() {
  QPushButton *key = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + key->text());
  error(calc_.add_operator(key->text().toStdString()));
}

void s21_smart_calc_MW::var_operations() {
  QPushButton *key = (QPushButton *)sender();
  ui->label->setText(ui->label->text() + key->text());
  calc_.add_variable(ui->doubleSpinBox->value());
}

void s21_smart_calc_MW::key_functions() {
  QPushButton *key = (QPushButton *)sender();
  if (key->text().contains("√")) {
    ui->label->setText(ui->label->text() + "sqrt" + '(');
    error(calc_.add_function("sqrt"));
  } else {
    ui->label->setText(ui->label->text() + key->text() + '(');
    error(calc_.add_function(key->text().toStdString()));
  }
  error(calc_.add_operator("("));
}

void s21_smart_calc_MW::on_pushButton_dot_clicked() {
  ui->label->setText(ui->label->text() + ".");
  error(calc_.add_number("."));
}

void s21_smart_calc_MW::on_pushButton_clear_clicked() {
  calc_.clear();
  ui->label->clear();
}

void s21_smart_calc_MW::on_pushButton_credit_clicked() {
  credit_window = new credit_calc(this);
  credit_window->setModal(true);
  credit_window->exec();
}

void s21_smart_calc_MW::on_pushButton_exp_clicked() {
  ui->label->setText(ui->label->text() + "e");
  calc_.add_exp();
}

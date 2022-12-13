#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "controller.h"

TEST(test, test1) {
  s21::Controller a;
  a.add_number("2");
  a.add_number("2");

  a.add_number(".");
  a.add_number("5");
  a.add_operator("+");
  a.add_number("1");
  a.add_number(".");
  a.add_number("5");

  a.polish_notation();
  EXPECT_EQ(24, a.calc_notation().first);
}

TEST(test, test3) {
  s21::Controller a;
  a.add_number("22");
  a.add_number(".");
  a.add_number("5");
  a.add_operator("+");
  a.add_operator("(");
  a.add_operator("-");
  a.add_number("1");
  a.add_number(".");
  a.add_number("5");
  a.add_operator("*");
  a.add_number("2");
  a.add_operator(")");

  a.polish_notation();
  EXPECT_EQ(19.5, a.calc_notation().first);
}

TEST(test, test4) {
  s21::Controller a;
  a.add_operator("-");
  a.add_number("102");
  a.polish_notation();
  EXPECT_EQ(-102, a.calc_notation().first);
}

TEST(test, test5) {
  s21::Controller a;
  a.add_operator("-");
  a.add_variable(1.5);
  a.polish_notation();
  a.set_x(5);
  EXPECT_EQ(-5, a.calc_notation().first);
}

TEST(test, test6) {
  s21::Controller a;
  s21::Controller b;
  a.add_operator("-");
  a.add_variable(1.5);
  a.polish_notation();
  a = b;
  a.set_x(5);
  b.set_x(5);
  EXPECT_EQ(b.calc_notation().first, a.calc_notation().first);
}

TEST(test, test7) {
  s21::Controller a;
  a.add_number("22");
  a.add_number(".");
  a.add_number("5");
  a.add_operator("-");
  a.add_operator("(");
  a.add_number("5");
  a.add_operator("/");
  a.add_number("1");
  a.add_number(".");
  a.add_number("5");
  a.add_operator("%");
  a.add_number("2");
  a.add_operator(")");

  a.polish_notation();
  EXPECT_EQ(22.5 - fmod((5 / 1.5), 2), a.calc_notation().first);
}

TEST(test, test8) {
  s21::Controller a;
  a.add_function("sin");
  a.add_operator("(");
  a.add_number("22");
  a.add_operator("-");
  a.add_number("5");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(sin(22 - 5), a.calc_notation().first);
}

TEST(test, test9) {
  s21::Controller a;
  a.add_function("asin");
  a.add_operator("(");
  a.add_number("0.22");
  a.add_operator("-");
  a.add_number("0.005");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(asin(0.22 - 0.005), a.calc_notation().first);
}

TEST(test, test10) {
  s21::Controller a;
  a.add_function("cos");
  a.add_operator("(");
  a.add_number("3.14");
  a.add_operator("/");
  a.add_number("2");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(cos(3.14 / 2), a.calc_notation().first);
}

TEST(test, test11) {
  s21::Controller a;
  a.add_function("acos");
  a.add_operator("(");
  a.add_number("3.14");
  a.add_operator("/");
  a.add_number("4");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(acos(3.14 / 4), a.calc_notation().first);
}

TEST(test, test12) {
  s21::Controller a;
  a.add_function("tan");
  a.add_operator("(");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number("11");
  a.add_operator(")");
  a.add_operator("/");
  a.add_function("cos");
  a.add_operator("(");
  a.add_number("1.11");
  a.add_operator(")");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(tan(sin(11) / cos(1.11)), a.calc_notation().first);
}

TEST(test, test13) {
  s21::Controller a;
  a.add_function("atan");
  a.add_operator("(");
  a.add_number("0.346");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(atan(0.346), a.calc_notation().first);
}

TEST(test, test14) {
  s21::Controller a;
  a.add_function("log");
  a.add_operator("(");
  a.add_number("1000");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(log10(1000), a.calc_notation().first);
}

TEST(test, test15) {
  s21::Controller a;
  a.add_function("ln");
  a.add_operator("(");
  a.add_number("123456");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(log(123456), a.calc_notation().first);
}

TEST(test, test16) {
  s21::Controller a;
  a.add_function("sqrt");
  a.add_operator("(");
  a.add_number("123.45600006");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(sqrt(123.45600006), a.calc_notation().first);
}

TEST(test, test17) {
  s21::Controller a;
  a.add_function("sqrt");
  a.add_operator("(");
  a.add_number("123.45600006");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(false, a.empty());
  a.clear();
  EXPECT_EQ(true, a.empty());
}

TEST(test, test18) {
  s21::Element a;
  EXPECT_EQ(a.get_priority(), 0);
  EXPECT_EQ(a.get_type_obj(), 0);
  EXPECT_EQ(a.get_sign(), '\0');
  EXPECT_EQ(a.get_value(), 0);
}

TEST(test, test19) {
  double eps = 1e-7;
  s21::Controller a;
  a.add_number(123.45600006);
  a.add_operator("-");
  a.add_number("1");
  a.polish_notation();
  EXPECT_LT((fabs(123.45600006 - 1) - fabs(a.calc_notation().first)),
            fabs(eps));
  a.fix_result(std::to_string(a.calc_notation().first));
  a.add_operator("-");
  a.add_number(123.45600006);
  a.polish_notation();
  EXPECT_LT(fabs(-1) - fabs(a.calc_notation().first), fabs(eps));
}

TEST(test, test20) {
  s21::Controller a;
  a.add_operator("+");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator("+");
  a.add_operator("(");
  a.add_operator("-");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator(")");
  a.polish_notation();
  EXPECT_EQ(0, a.calc_notation().first);
}

TEST(test, test21) {
  s21::Controller a;
  a.add_number(123.45600006);
  a.add_exp();
  a.add_number(-2);
  a.polish_notation();
  EXPECT_EQ(1.2345600006, a.calc_notation().first);
}

TEST(test, test22) {
  s21::Controller a;
  a.add_operator("+");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator("+");
  a.add_operator("(");
  a.add_operator("-");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator(")");
  a.polish_notation();
  s21::Controller b;
  b.set_model(a.get_model());
  EXPECT_EQ(b.calc_notation().first, a.calc_notation().first);
}

// HAVE LEAKS IF MACOS

TEST(test, test23) {
  s21::Element a(15.3);
  EXPECT_EQ(a.get_type_obj(), 0);
}

TEST(test, test24) {
  s21::Controller a;
  EXPECT_EQ(true, a.add_function("zxic"));
}

TEST(test, test25) {
  s21::Controller a;
  EXPECT_EQ(true, a.add_number("zxcxxic"));
}

TEST(test, test26) {
  s21::Controller a;
  EXPECT_EQ(true, a.add_operator("&--"));
}

//

TEST(test, test27) {
  s21::Controller a;
  a.add_operator("+");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator("+");
  a.add_operator("(");
  a.add_operator("-");
  a.add_function("sin");
  a.add_operator("(");
  a.add_number(123.45600006);
  a.add_operator(")");
  a.add_operator("(");
  a.polish_notation();
  EXPECT_EQ(a.calc_notation().second, true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

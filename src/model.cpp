#include "model.h"

namespace s21 {

Model::Model() : flag_unary_(false), count_dot(0) {}

std::vector<Element> &Model::get_vector() { return list_; }

std::list<Element> &Model::get_list() { return polish_; }

void Model::inf_to_polish() {
  std::vector<Element> data = list_;
  std::list<Element> oper_stack_;
  for (unsigned int i = 0; i < data.size(); i++) {
    if (data[i].is_num() || data[i].is_variable()) {
      polish_.push_back(data[i]);
    } else if (data[i].is_brace()) {
      if (data[i].is_open_brace()) {
        oper_stack_.push_back(data[i]);
      } else {
        while (!oper_stack_.empty()) {
          if (oper_stack_.back().is_open_brace()) {
            oper_stack_.pop_back();
            break;
          } else {
            from_list_to_list(oper_stack_, polish_);
          }
        }
      }
    } else if (data[i].is_operator() || data[i].is_foo() ||
               data[i].is_unary()) {
      if (oper_stack_.empty()) {
        oper_stack_.push_back(data[i]);
      } else if (oper_stack_.back().get_priority() >= data[i].get_priority() &&
                 data[i].get_sign() != '^') {
        while (!oper_stack_.empty() &&
               oper_stack_.back().get_priority() >= data[i].get_priority()) {
          from_list_to_list(oper_stack_, polish_);
        }
        oper_stack_.push_back(data[i]);
      } else {
        oper_stack_.push_back(data[i]);
      }
    }
  }
  while (!oper_stack_.empty()) {
    from_list_to_list(oper_stack_, polish_);
  }
}

double Model::calc_polish() {
  std::list<Element> result;
  std::list<Element> copy_polish = polish_;
  while (!copy_polish.empty()) {
    if (copy_polish.front().is_num() || copy_polish.front().is_variable()) {
      from_list_to_list_front(copy_polish, result);
    } else if (copy_polish.front().is_operator()) {
      std::pair<double, double> tmp;
      tmp = pop_binary_ops(result);
      switch (copy_polish.front().get_sign()) {
        case '+':
          result.push_back(Element((tmp.second + tmp.first)));
          copy_polish.pop_front();
          break;
        case '-':
          result.push_back(Element((tmp.second - tmp.first)));
          copy_polish.pop_front();
          break;
        case '*':
          result.push_back(Element((tmp.second * tmp.first)));
          copy_polish.pop_front();
          break;
        case '/':
          result.push_back(Element((tmp.second / tmp.first)));
          copy_polish.pop_front();
          break;
        case '%':
          result.push_back(Element((fmod(tmp.second, tmp.first))));
          copy_polish.pop_front();
          break;
        case '^':
          result.push_back(Element((pow(tmp.second, tmp.first))));
          copy_polish.pop_front();
          break;
        default:
          throw std::invalid_argument("Unknown operator");
          break;
      }
    } else if (copy_polish.front().is_foo() || copy_polish.front().is_unary()) {
      double tmp = pop_unary_ops(result);
      switch (copy_polish.front().get_sign()) {
        case 's':
          result.push_back(Element(sin(tmp)));
          copy_polish.pop_front();
          break;
        case 'z':
          result.push_back(Element(asin(tmp)));
          copy_polish.pop_front();
          break;
        case 'c':
          result.push_back(Element(cos(tmp)));
          copy_polish.pop_front();
          break;
        case 'a':
          result.push_back(Element(acos(tmp)));
          copy_polish.pop_front();
          break;
        case 't':
          result.push_back(Element(tan(tmp)));
          copy_polish.pop_front();
          break;
        case 'd':
          result.push_back(Element(atan(tmp)));
          copy_polish.pop_front();
          break;
        case 'l':
          result.push_back(Element(log10(tmp)));
          copy_polish.pop_front();
          break;
        case 'm':
          result.push_back(Element(log(tmp)));
          copy_polish.pop_front();
          break;
        case 'q':
          result.push_back(Element(sqrt(tmp)));
          copy_polish.pop_front();
          break;
        case '~':
          result.push_back(Element(tmp * (-1)));
          copy_polish.pop_front();
          break;
        case '#':
          result.push_back(Element(tmp));
          copy_polish.pop_front();
          break;
        default:
          throw std::invalid_argument("Unknown function");
          break;
      }
    } else {
      throw std::invalid_argument("error brace");
    }
  }
  if (copy_polish.empty() && result.size() > 1)
    throw std::invalid_argument("count of elements is error");
  return result.front().get_value();
}

double Model::pop_unary_ops(std::list<Element> &current) {
  double results;
  if (current.back().is_num() || current.back().is_variable()) {
    results = current.back().get_value();
    current.pop_back();
  } else {
    throw std::invalid_argument("incorrect data unary ops");
  }
  return results;
}

std::pair<double, double> Model::pop_binary_ops(std::list<Element> &current) {
  std::pair<double, double> results;
  if (current.back().is_num() || current.back().is_variable()) {
    results.first = current.back().get_value();
    current.pop_back();
    if (current.back().is_num() || current.back().is_variable()) {
      results.second = current.back().get_value();
      current.pop_back();
    } else {
      throw std::invalid_argument("incorrect data binary ops");
    }
  } else {
    throw std::invalid_argument("incorrect data binary ops");
  }
  return results;
}

bool Model::check_operators(char sign) {
  switch (sign) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '(':
    case ')':
    case '^':
      return false;
    default:
      return true;
  }
}
void Model::from_list_to_list(std::list<Element> &input,
                              std::list<Element> &output) {
  output.push_back(input.back());
  input.pop_back();
}

void Model::from_list_to_list_front(std::list<Element> &input,
                                    std::list<Element> &output) {
  output.push_back(input.front());
  input.pop_front();
}

void Model::add_number(const std::string &input_str) {
  if (input_str == ".") count_dot++;
  if (count_dot > 1) throw std::invalid_argument("should be 1 dot");
  if (list_.empty()) {
    num_ = input_str;
    add_num(std::stod(input_str));
  } else if (list_.back().is_num()) {
    num_ += input_str;
    list_.back().set_value(std::stof(num_));
  } else {
    num_.clear();
    count_dot = 0;
    num_ = input_str;
    add_num(std::stod(input_str));
  }
  flag_unary_ = false;
}

void Model::add_number(double value) {
  add_num(value);
  flag_unary_ = false;
}

void Model::add_num(double value) { list_.push_back(Element(value)); }
void Model::add_operator(std::string str) {
  if (list_.empty()) flag_unary_ = true;
  if (flag_unary_ == true && (str.front() == '+' || str.front() == '-')) {
    add_unary(str.front());
    flag_unary_ = false;
  } else {
    add_element(str.front());
  }
  if (str.front() == '(' || str.front() == '^') {
    flag_unary_ = true;
  } else {
    flag_unary_ = false;
  }
}

void Model::add_element(char sign) {
  if (check_operators(sign)) throw std::invalid_argument("Error operator");
  list_.push_back(Element(sign));
}

void Model::add_function(const std::string &foo) {
  if (foo == "sin") {
    list_.push_back(Element('s'));
  } else if (foo == "asin") {
    list_.push_back(Element('z'));
  } else if (foo == "cos") {
    list_.push_back(Element('c'));
  } else if (foo == "acos") {
    list_.push_back(Element('a'));
  } else if (foo == "tan") {
    list_.push_back(Element('t'));
  } else if (foo == "atan") {
    list_.push_back(Element('d'));
  } else if (foo == "log") {
    list_.push_back(Element('l'));
  } else if (foo == "ln") {
    list_.push_back(Element('m'));
  } else if (foo == "sqrt") {
    list_.push_back(Element('q'));
  } else {
    throw std::invalid_argument("Error function");
  }
  flag_unary_ = false;
}

void Model::add_variable(double value) {
  list_.push_back(Element('x', value));
  flag_unary_ = false;
}

void Model::add_unary(char sign) {
  if (sign == '+')
    list_.push_back(Element('#', true));
  else if (sign == '-')
    list_.push_back(Element('~', true));
  else
    throw std::invalid_argument("unary op error");
}

void Model::set_value_x(double value) {
  for (auto it = polish_.begin(); it != polish_.end(); ++it) {
    if ((*it).is_variable()) {
      (*it).set_value(value);
    }
  }
}

void Model::clear() {
  if (!list_.empty()) list_.clear();
  if (!polish_.empty()) polish_.clear();
  count_dot = 0;
  num_.clear();
  flag_unary_ = false;
}

}  // namespace s21

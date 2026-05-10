#include "calculator.h"
#include "mathlib.h"
#include <stdexcept>

int Calculator::calculate(const Expression &expression) const {
  int result = 0;
  int rc = mathlib::MATH_OK;

  switch (expression.op()) {
  case '+':
    rc = mathlib::math_add(expression.a(), expression.b(), &result);
    break;
  case '-':
    rc = mathlib::math_sub(expression.a(), expression.b(), &result);
    break;
  case 'x':
    rc = mathlib::math_mul(expression.a(), expression.b(), &result);
    break;
  case '/':
    rc = mathlib::math_div(expression.a(), expression.b(), &result);
    break;
  case '^':
    rc = mathlib::math_pow(expression.a(), expression.b(), &result);
    break;
  case '!':
    rc = mathlib::math_fact(expression.a(), &result);
    break;
  default:
    throw std::runtime_error("unknown operation");
  }

  if (rc == mathlib::MATH_ERR_OVERFLOW) {
    throw std::runtime_error("overflow");
  }

  if (rc == mathlib::MATH_ERR_DIV_BY_ZERO) {
    throw std::runtime_error("division by zero");
  }

  if (rc == mathlib::MATH_ERR_INVALID_ARG) {
    throw std::runtime_error("invalid argument");
  }

  if (rc != mathlib::MATH_OK) {
    throw std::runtime_error("math error");
  }

  return result;
}
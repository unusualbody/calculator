#include "checker.h"
#include <stdexcept>

void Checker::check(const Expression &expression) const {
  const char op = expression.op();

  if (op == '!') {
    if (expression.hasB()) {
      throw std::runtime_error("'!' must be used in unary form");
    }

    if (expression.a() < 0) {
      throw std::runtime_error("factorial requires n >= 0");
    }

    return;
  }

  if (!isBinaryOperation(op)) {
    throw std::runtime_error("unknown operation");
  }

  if (!expression.hasB()) {
    throw std::runtime_error("binary operation requires second operand");
  }

  if (op == '^' && expression.b() < 0) {
    throw std::runtime_error("power requires exp >= 0");
  }

  if (op == '/' && expression.b() == 0) {
    throw std::runtime_error("division by zero");
  }
}

bool Checker::isBinaryOperation(char op) const {
  return op == '+' || op == '-' || op == 'x' || op == '/' || op == '^';
}
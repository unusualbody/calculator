#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "expression.h"

class Calculator {
public:
  Calculator() = default;
  ~Calculator() = default;

  Calculator(const Calculator &) = default;
  Calculator &operator=(const Calculator &) = default;

  Calculator(Calculator &&) noexcept = default;
  Calculator &operator=(Calculator &&) noexcept = default;

  int calculate(const Expression &expression) const;
};

#endif // CALCULATOR_H
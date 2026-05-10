#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "expression.h"

class Calculator {
public:
  int calculate(const Expression &expression) const;
};

#endif // CALCULATOR_H
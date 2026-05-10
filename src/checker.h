#ifndef CHECKER_H
#define CHECKER_H

#include "expression.h"

class Checker {
public:
  void check(const Expression &expression) const;

private:
  bool isBinaryOperation(char op) const;
};

#endif // CHECKER_H
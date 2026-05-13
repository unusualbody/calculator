#ifndef CHECKER_H
#define CHECKER_H

#include "expression.h"

class Checker {
public:
  Checker() = default;
  ~Checker() = default;

  Checker(const Checker &) = default;
  Checker &operator=(const Checker &) = default;

  Checker(Checker &&) noexcept = default;
  Checker &operator=(Checker &&) noexcept = default;

  void check(const Expression &expression) const;

private:
  bool isBinaryOperation(char op) const;
};

#endif // CHECKER_H
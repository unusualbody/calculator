#ifndef PRINTER_H
#define PRINTER_H

#include "expression.h"

class Printer {
public:
  Printer() = default;
  ~Printer() = default;

  Printer(const Printer &) = default;
  Printer &operator=(const Printer &) = default;

  Printer(Printer &&) noexcept = default;
  Printer &operator=(Printer &&) noexcept = default;

  void printHelp(const char *prog) const;
  void printResult(const Expression &expression, int result) const;
  void printError(const char *fmt, ...) const;
};

#endif // PRINTER_H
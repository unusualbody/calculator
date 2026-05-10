#ifndef PRINTER_H
#define PRINTER_H

#include "expression.h"

class Printer {
public:
  void printHelp(const char *prog) const;
  void printResult(const Expression &expression, int result) const;
  void printError(const char *fmt, ...) const;
};

#endif // PRINTER_H
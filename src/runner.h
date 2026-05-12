#ifndef RUNNER_H
#define RUNNER_H

#include "calculator.h"
#include "checker.h"
#include "parser.h"
#include "printer.h"

class Runner {
public:
  Runner() = default;
  ~Runner() = default;

  Runner(const Runner &) = default;
  Runner &operator=(const Runner &) = default;

  Runner(Runner &&) noexcept = default;
  Runner &operator=(Runner &&) noexcept = default;

  int run(int argc, char **argv) const;

private:
  Printer printer_;
  Parser parser_;
  Checker checker_;
  Calculator calculator_;
};

#endif // RUNNER_H
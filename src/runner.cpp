#include "runner.h"
#include "calculator.h"
#include "checker.h"
#include "parser.h"
#include "printer.h"
#include <exception>

int Runner::run(int argc, char **argv) const {
  Printer printer;

  if (argc == 2 && (std::strcmp(argv[1], "-h") == 0 ||
                    std::strcmp(argv[1], "--help") == 0)) {
    printer.printHelp(argv[0]);
    return 0;
  }

  try {
    Parser parser;
    Checker checker;
    Calculator calculator;

    const Expression expression = parser.parse(argc, argv);
    checker.check(expression);

    const int result = calculator.calculate(expression);
    printer.printResult(expression, result);

    return 0;
  } catch (const std::exception &e) {
    printer.printError("%s", e.what());
    printer.printHelp(argv[0]);
    return 1;
  }
}
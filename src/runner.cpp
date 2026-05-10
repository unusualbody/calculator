#include "runner.h"
#include "calculator.h"
#include "checker.h"
#include "logger.h"
#include "parser.h"
#include "printer.h"
#include <exception>

int Runner::run(int argc, char **argv) const {
  Printer printer;

  if (argc == 2 && (std::strcmp(argv[1], "-h") == 0 ||
                    std::strcmp(argv[1], "--help") == 0)) {
    Logger::instance().info("show help");
    printer.printHelp(argv[0]);
    return 0;
  }

  try {
    Logger::instance().info("start calculation");

    Parser parser;
    Checker checker;
    Calculator calculator;

    const Expression expression = parser.parse(argc, argv);
    checker.check(expression);

    const int result = calculator.calculate(expression);
    printer.printResult(expression, result);

    Logger::instance().info("calculation finished");

    return 0;
  } catch (const std::exception &e) {
    Logger::instance().error(e.what());
    printer.printError("%s", e.what());
    printer.printHelp(argv[0]);
    return 1;
  }
}
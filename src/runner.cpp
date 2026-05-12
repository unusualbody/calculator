#include "runner.h"
#include "logger.h"
#include <exception>

int Runner::run(int argc, char **argv) const {
  if (argc == 2 && (std::strcmp(argv[1], "-h") == 0 ||
                    std::strcmp(argv[1], "--help") == 0)) {
    Logger::instance().info("show help");
    printer_.printHelp(argv[0]);
    return 0;
  }

  try {
    Logger::instance().info("start calculation");

    const Expression expression = parser_.parse(argc, argv);
    checker_.check(expression);

    const int result = calculator_.calculate(expression);
    printer_.printResult(expression, result);

    Logger::instance().info("calculation finished");

    return 0;
  } catch (const std::exception &e) {
    Logger::instance().error(e.what());
    printer_.printError("%s", e.what());
    printer_.printHelp(argv[0]);
    return 1;
  }
}
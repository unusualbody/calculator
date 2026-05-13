#include "logger.h"
#include "runner.h"
#include <exception>

int main(int argc, char **argv) {
  try {
    Runner runner;
    return runner.run(argc, argv);
  } catch (const std::exception &e) {
    Logger::instance().error(e.what());
    return 1;
  } catch (...) {
    Logger::instance().error("unknown error");
    return 1;
  }
}
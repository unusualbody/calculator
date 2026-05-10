#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

Logger &Logger::instance() {
  static Logger logger;
  return logger;
}

Logger::Logger() {
  spdlog::set_default_logger(spdlog::stderr_color_mt("calculator"));
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
}

void Logger::info(const char *message) const { spdlog::info(message); }

void Logger::error(const char *message) const { spdlog::error(message); }
#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
  static Logger &instance();

  void info(const char *message) const;
  void error(const char *message) const;

private:
  Logger();
  ~Logger() = default;

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;
  Logger &operator=(Logger &&) = delete;
};

#endif // LOGGER_H
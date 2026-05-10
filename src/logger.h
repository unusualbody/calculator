#ifndef LOGGER_H
#define LOGGER_H

class Logger {
public:
  static Logger &instance();

  void info(const char *message) const;
  void error(const char *message) const;

private:
  Logger();

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;
};

#endif // LOGGER_H
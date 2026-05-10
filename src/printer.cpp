#include "printer.h"
#include <cstdarg>
#include <cstdio>

void Printer::printHelp(const char *prog) const {
  printf("Usage (JSON):\n"
         "  %s '{\"a\":2,\"b\":3,\"op\":\"+\"}'\n"
         "  %s '{\"a\":5,\"op\":\"!\"}'\n"
         "\n"
         "JSON fields:\n"
         "  a   integer, first operand\n"
         "  b   integer, second operand; required for binary operations\n"
         "  op  string with one operation character\n"
         "\n"
         "Operations:\n"
         "  +  addition\n"
         "  -  subtraction\n"
         "  x  multiplication\n"
         "  /  division\n"
         "  ^  power\n"
         "  !  factorial\n"
         "\n"
         "Options:\n"
         "  -h, --help    show this help\n",
         prog, prog);
}

void Printer::printResult(const Expression &expression, int result) const {
  switch (expression.op()) {
  case '!':
    printf("fact(%d) = %d\n", expression.a(), result);
    break;
  case '^':
    printf("%d^%d = %d\n", expression.a(), expression.b(), result);
    break;
  case 'x':
    printf("%d x %d = %d\n", expression.a(), expression.b(), result);
    break;
  default:
    printf("%d %c %d = %d\n", expression.a(), expression.op(), expression.b(),
           result);
    break;
  }
}

void Printer::printError(const char *fmt, ...) const {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
}
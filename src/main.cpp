#include "mathlib.h"
#include <cerrno>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

static void print_help(const char *prog) {
  printf("Usage (RPN):\n"
         "  %s A B OP\n"
         "  %s N !\n"
         "\n"
         "Operations:\n"
         "  +  addition\n"
         "  -  subtraction\n"
         "  x  multiplication (use 'x' instead of '*')\n"
         "  /  division\n"
         "  ^  power\n"
         "  !  factorial\n"
         "\n"
         "Options:\n"
         "  -h, --help   show this help\n",
         prog, prog);
}

static void print_error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "Error: ");
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
}

static int parse_int(const char *s, int *out) {
  char *end = nullptr;
  errno = 0;

  long v = strtol(s, &end, 10);

  if (errno != 0)
    return -1;
  if (end == s)
    return -1; // no digits
  if (*end != '\0')
    return -1; // extra characters
  if (v < INT_MIN || v > INT_MAX)
    return -1;
  *out = (int)v;

  return 0;
}

static int run_unary(int n, char op) {
  if (op != '!') {
    print_error("expected '!'");
    return 1;
  }

  int result = math_fact(n);
  printf("fact(%d) = %d\n", n, result);

  return 0;
}

static int run_binary(int a, int b, char op) {
  int result = 0;

  switch (op) {
  case '+':
    result = math_add(a, b);
    printf("%d + %d = %d\n", a, b, result);
    return 0;
  case '-':
    result = math_sub(a, b);
    printf("%d - %d = %d\n", a, b, result);
    return 0;
  case 'x':
    result = math_mul(a, b);
    printf("%d x %d = %d\n", a, b, result);
    return 0;
  case '^':
    result = math_pow(a, b);
    printf("%d^%d = %d\n", a, b, result);
    return 0;
  case '/':
    if (math_div(a, b, &result) != 0) {
      print_error("division by zero");
      return 2;
    }
    printf("%d / %d = %d\n", a, b, result);
    return 0;
  default:
    print_error("unknown operation");
    return 1;
  }
}

int main(int argc, char **argv) {
  static struct option long_opts[] = {{"help", no_argument, 0, 'h'},
                                      {0, 0, 0, 0}};

  int opt;
  while ((opt = getopt_long(argc, argv, "h", long_opts, NULL)) != -1) {
    switch (opt) {
    case 'h':
      print_help(argv[0]);
      return 0;
    default:
      print_help(argv[0]);
      return 1;
    }
  }

  const int remaining = argc - optind;

  if (remaining != 2 && remaining != 3) {
    print_error("invalid number of arguments");
    print_help(argv[0]);
    return 1;
  }

  // unary: N !
  if (remaining == 2) {
    int n = 0;
    const char *n_str = argv[optind];
    const char *op_str = argv[optind + 1];

    if (parse_int(n_str, &n) != 0) {
      print_error("invalid integer: %s", n_str);
      return 1;
    }

    if (op_str[1] != '\0') {
      print_error("operation must be a single character");
      print_help(argv[0]);
      return 1;
    }

    int result = run_unary(n, op_str[0]);
    if (result != 0) {
      print_help(argv[0]);
    }

    return result;
  }

  // binary: A B OP
  int a = 0;
  int b = 0;
  const char *a_str = argv[optind];
  const char *b_str = argv[optind + 1];
  const char *op_str = argv[optind + 2];

  if (parse_int(a_str, &a) != 0) {
    print_error("invalid integer: %s", a_str);
    return 1;
  }

  if (parse_int(b_str, &b) != 0) {
    print_error("invalid integer: %s", b_str);
    return 1;
  }

  if (op_str[1] != '\0') {
    print_error("operation must be a single character");
    print_help(argv[0]);
    return 1;
  }

  int result = run_binary(a, b, op_str[0]);
  if (result == 1) {
    print_help(argv[0]);
  }

  return result;
}

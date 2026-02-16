#include "mathlib.h"

#include <cerrno>
#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

struct CalcData
{
    int a;
    int b;
    char op;
    int result;
};

static void print_help(const char* prog)
{
    printf("Usage (RPN):\n"
           "  %s A B OP\n"
           "  %s N !\n"
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

static void print_error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}

static void print_math_error(int rc)
{
    switch (rc) {
    case mathlib::MATH_ERR_OVERFLOW:
        print_error("overflow");
        break;
    case mathlib::MATH_ERR_DIV_BY_ZERO:
        print_error("division by zero");
        break;
    case mathlib::MATH_ERR_INVALID_ARG:
        print_error("invalid argument");
        break;
    default:
        print_error("math error (code=%d)", rc);
        break;
    }
}

static void print_result(const CalcData* d)
{
    switch (d->op) {
    case '!':
        printf("fact(%d) = %d\n", d->a, d->result);
        break;
    case '^':
        printf("%d^%d = %d\n", d->a, d->b, d->result);
        break;
    case 'x':
        printf("%d x %d = %d\n", d->a, d->b, d->result);
        break;
    default:
        printf("%d %c %d = %d\n", d->a, d->op, d->b, d->result);
        break;
    }
}

static int parse_int(const char* s, int* out)
{
    char* end = nullptr;
    errno = 0;

    long v = strtol(s, &end, 10);

    if (errno == ERANGE) return -1;
    if (errno != 0) return -1;
    if (end == s) return -1;
    if (*end != '\0') return -1;
    if (v < (long)INT_MIN || v > (long)INT_MAX) return -1;
    *out = (int)v;

    return 0;
}

static int is_binary_op(char op)
{
    return (op == '+' || op == '-' || op == 'x' || op == '/' || op == '^');
}

static int is_negative_number_token(const char* s)
{
    return (s && s[0] == '-' && s[1] >= '0' && s[1] <= '9');
}

// return: 0 - ok; 1 - usage/help requested; 2 - usage error
static int parse(CalcData* d, int argc, char** argv, int* want_help)
{
    *want_help = 0;
    static struct option long_opts[] = {{"help", no_argument, 0, 'h'},
                                        {0, 0, 0, 0}};
    optind = 1;
    opterr = 0;

    int opt;
    int stop_options = 0;

    while (!stop_options &&
            (opt = getopt_long(argc, argv, "+h", long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'h': {
            *want_help = 1;
            return 1;
        }
        case '?': {
            const char* bad = argv[optind - 1];

            if (is_negative_number_token(bad)) {
                optind -= 1;
                stop_options = 1;
                break;
            }

            print_error("unknown option: %s", bad);

            return 2;
        }
        default: {
            print_error("unknown option");
            return 2;
        }
        }
    }

    int remaining = argc - optind;
    if (remaining != 2 && remaining != 3) {
        print_error("invalid number of arguments");
        return 2;
    }

    d->a = 0;
    d->b = 0;
    d->op = 0;
    d->result = 0;

    if (remaining == 2) {
        // N !
        if (parse_int(argv[optind], &d->a) != 0) {
            print_error("invalid integer: %s", argv[optind]);
            return 2;
        }
    
        const char* op = argv[optind + 1];
        if (!op || op[0] == '\0' || op[1] != '\0') {
            print_error("operation must be a single character");
            return 2;
        }

        d->op = op[0];

        if (d->op != '!') {
            print_error("unary form requires '!': N !");
            return 2;
        }

        return 0;
    }

    // A B OP
    if (parse_int(argv[optind], &d->a) != 0) {
        print_error("invalid integer: %s", argv[optind]);
        return 2;
    }

    if (parse_int(argv[optind + 1], &d->b) != 0) {
        print_error("invalid integer: %s", argv[optind + 1]);
        return 2;
    }

    const char* op = argv[optind + 2];
    if (!op || op[0] == '\0' || op[1] != '\0') {
        print_error("operation must be a single character");
        return 2;
    }

    d->op = op[0];

    return 0;
}

// return: 0 - ok; 1 - usage error; 2 - runtime error
static int check(const CalcData* d)
{
    if (d->op == '!') {
        if (d->b != 0) {
            print_error("'!' must be used in unary form: N !");
            return 1;
        }

        if (d->a < 0) {
            print_error("factorial requires n >= 0");
            return 2;
        }

        return 0;
    }

    if (!is_binary_op(d->op)) {
        print_error("unknown operation");
        return 1;
    }

    if (d->op == '^' && d->b < 0) {
        print_error("power requires exp >= 0");
        return 2;
    }

    if (d->op == '/' && d->b == 0) {
        print_error("division by zero");
        return 2;
    }

    return 0;
}

// return: 0 - ok; 2 - runtime error
static int calculate(CalcData* d)
{
    int rc = mathlib::MATH_OK;

    switch (d->op) {
    case '+':
        rc = mathlib::math_add(d->a, d->b, &d->result);
        break;
    case '-':
        rc = mathlib::math_sub(d->a, d->b, &d->result);
        break;
    case 'x':
        rc = mathlib::math_mul(d->a, d->b, &d->result);
        break;
    case '/':
        rc = mathlib::math_div(d->a, d->b, &d->result);
        break;
    case '^':
        rc = mathlib::math_pow(d->a, d->b, &d->result);
        break;
    case '!':
        rc = mathlib::math_fact(d->a, &d->result);
        break;
    default:
        return 2;
    }

    if (rc != mathlib::MATH_OK) {
        print_math_error(rc);
        return 2;
    }

    return 0;
}

static int run(int argc, char** argv)
{
    CalcData d;
    int want_help = 0;

    int prc = parse(&d, argc, argv, &want_help);
    if (want_help) {
        print_help(argv[0]);
        return 0;
    }

    if (prc != 0) {
        print_help(argv[0]);
        return 1;
    }

    switch (check(&d)) {
    case 0:
        break;
    case 1:
        print_help(argv[0]);
        return 1;
    case 2:
        return 2;
    default:
        return 2;
    }

    int calc_rc = calculate(&d);
    if (calc_rc != 0) {
        return 2;
    }

    print_result(&d);

    return 0;
}

int main(int argc, char** argv)
{
    return run(argc, argv);
}


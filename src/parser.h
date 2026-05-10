#ifndef PARSER_H
#define PARSER_H

#include "expression.h"
#include <nlohmann/json.hpp>

class Parser {
public:
  Expression parse(int argc, char **argv) const;

private:
  int getRequiredInt(const nlohmann::json &json, const char *name) const;
  char getRequiredOp(const nlohmann::json &json) const;
};

#endif // PARSER_H
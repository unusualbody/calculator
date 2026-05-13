#include "parser.h"
#include <stdexcept>
#include <string>

Expression Parser::parse(int argc, char **argv) const {
  if (argc != 2) {
    throw std::runtime_error("invalid number of arguments");
  }

  nlohmann::json json;

  try {
    json = nlohmann::json::parse(argv[1]);
  } catch (const nlohmann::json::parse_error &) {
    throw std::runtime_error("invalid json");
  }

  if (!json.is_object()) {
    throw std::runtime_error("json must be an object");
  }

  const int a = getRequiredInt(json, "a");
  const char op = getRequiredOp(json);

  if (op == '!') {
    if (json.contains("b")) {
      throw std::runtime_error("'!' must be used in unary form");
    }

    return Expression{a, 0, op, false};
  }

  const int b = getRequiredInt(json, "b");

  return Expression{a, b, op, true};
}

int Parser::getRequiredInt(const nlohmann::json &json, const char *name) const {
  if (!json.contains(name)) {
    throw std::runtime_error(std::string("missing field: ") + name);
  }

  if (!json.at(name).is_number_integer()) {
    throw std::runtime_error(std::string("field must be integer: ") + name);
  }

  return json.at(name).get<int>();
}

char Parser::getRequiredOp(const nlohmann::json &json) const {
  if (!json.contains("op")) {
    throw std::runtime_error("missing field: op");
  }

  if (!json.at("op").is_string()) {
    throw std::runtime_error("field must be string: op");
  }

  const std::string op = json.at("op").get<std::string>();

  if (op.size() != 1) {
    throw std::runtime_error("operation must be a single character");
  }

  return op[0];
}
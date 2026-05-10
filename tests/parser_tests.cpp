#include "expression.h"
#include "parser.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(ParserTest, ParsesValidBinaryExpression) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":2,\"b\":3,\"op\":\"+\"}";
  char *argv[] = {arg0, arg1};
  const Expression expression = parser.parse(2, argv);
  EXPECT_EQ(expression.a(), 2);
  EXPECT_EQ(expression.b(), 3);
  EXPECT_EQ(expression.op(), '+');
  EXPECT_TRUE(expression.hasB());
}

TEST(ParserTest, ParsesValidFactorialExpression) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":5,\"op\":\"!\"}";
  char *argv[] = {arg0, arg1};
  const Expression expression = parser.parse(2, argv);
  EXPECT_EQ(expression.a(), 5);
  EXPECT_EQ(expression.op(), '!');
  EXPECT_FALSE(expression.hasB());
}

TEST(ParserTest, ThrowsOnInvalidNumberOfArguments) {
  Parser parser;
  char arg0[] = "calculator";
  char *argv[] = {arg0};
  EXPECT_THROW(parser.parse(1, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnInvalidJson) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{invalid json}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnJsonArray) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "[1,2,3]";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnMissingA) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"b\":3,\"op\":\"+\"}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnMissingBForBinaryOperation) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":2,\"op\":\"+\"}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnBForFactorial) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":5,\"b\":2,\"op\":\"!\"}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnNonIntegerA) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":\"2\",\"b\":3,\"op\":\"+\"}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnNonStringOp) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":2,\"b\":3,\"op\":1}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}

TEST(ParserTest, ThrowsOnLongOperation) {
  Parser parser;
  char arg0[] = "calculator";
  char arg1[] = "{\"a\":2,\"b\":3,\"op\":\"plus\"}";
  char *argv[] = {arg0, arg1};
  EXPECT_THROW(parser.parse(2, argv), std::runtime_error);
}
#include "checker.h"
#include "expression.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(CheckerTest, AcceptsValidBinaryExpression) {
  Checker checker;
  const Expression expression{2, 3, '+'};
  EXPECT_NO_THROW(checker.check(expression));
}

TEST(CheckerTest, AcceptsValidFactorialExpression) {
  Checker checker;
  const Expression expression{5, '!'};
  EXPECT_NO_THROW(checker.check(expression));
}

TEST(CheckerTest, ThrowsOnUnknownOperation) {
  Checker checker;
  const Expression expression{2, 3, '%'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnDivisionByZero) {
  Checker checker;
  const Expression expression{2, 0, '/'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnNegativePower) {
  Checker checker;
  const Expression expression{2, -1, '^'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnNegativeFactorial) {
  Checker checker;
  const Expression expression{-1, '!'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnFactorialWithSecondOperand) {
  Checker checker;
  const Expression expression{5, 2, '!'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnBinaryOperationWithoutSecondOperand) {
  Checker checker;
  const Expression expression{5, '+'};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}
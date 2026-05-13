#include "checker.h"
#include "expression.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(CheckerTest, AcceptsValidBinaryExpression) {
  Checker checker;
  const Expression expression{2, 3, '+', true};
  EXPECT_NO_THROW(checker.check(expression));
}

TEST(CheckerTest, AcceptsValidFactorialExpression) {
  Checker checker;
  const Expression expression{5, 0, '!', false};
  EXPECT_NO_THROW(checker.check(expression));
}

TEST(CheckerTest, ThrowsOnUnknownOperation) {
  Checker checker;
  const Expression expression{2, 3, '%', true};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnDivisionByZero) {
  Checker checker;
  const Expression expression{2, 0, '/', true};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnNegativePower) {
  Checker checker;
  const Expression expression{2, -1, '^', true};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnNegativeFactorial) {
  Checker checker;
  const Expression expression{-1, 0, '!', false};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnFactorialWithSecondOperand) {
  Checker checker;
  const Expression expression{5, 2, '!', true};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}

TEST(CheckerTest, ThrowsOnBinaryOperationWithoutSecondOperand) {
  Checker checker;
  const Expression expression{5, 0, '+', false};
  EXPECT_THROW(checker.check(expression), std::runtime_error);
}
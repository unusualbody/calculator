#include "calculator.h"
#include "expression.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(CalculatorTest, AddsTwoNumbers) {
  Calculator calculator;
  const Expression expression{2, 3, '+'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 5);
}

TEST(CalculatorTest, SubtractsTwoNumbers) {
  Calculator calculator;
  const Expression expression{7, 4, '-'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 3);
}

TEST(CalculatorTest, MultipliesTwoNumbers) {
  Calculator calculator;
  const Expression expression{6, 7, 'x'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 42);
}

TEST(CalculatorTest, DividesTwoNumbers) {
  Calculator calculator;
  const Expression expression{8, 2, '/'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 4);
}

TEST(CalculatorTest, CalculatesPower) {
  Calculator calculator;
  const Expression expression{2, 5, '^'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 32);
}

TEST(CalculatorTest, CalculatesFactorial) {
  Calculator calculator;
  const Expression expression{5, '!'};
  const int result = calculator.calculate(expression);
  EXPECT_EQ(result, 120);
}

TEST(CalculatorTest, ThrowsOnUnknownOperation) {
  Calculator calculator;
  const Expression expression{2, 3, '%'};
  EXPECT_THROW(calculator.calculate(expression), std::runtime_error);
}
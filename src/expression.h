#ifndef EXPRESSION_H
#define EXPRESSION_H

class Expression {
public:
  explicit Expression(int a, char op) : a_(a), b_(0), op_(op), has_b_(false) {}

  explicit Expression(int a, int b, char op)
      : a_(a), b_(b), op_(op), has_b_(true) {}

  int a() const { return a_; }

  int b() const { return b_; }

  char op() const { return op_; }

  bool hasB() const { return has_b_; }

private:
  int a_;
  int b_;
  char op_;
  bool has_b_;
};

#endif // EXPRESSION_H
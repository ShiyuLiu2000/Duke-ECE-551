#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>  // std
#include <sstream>   // std::stringstream
#include <vector>    // std::vector

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression {
  Expression * left;
  Expression * right;
  char op;

 public:
  OpExpression(Expression * lhs, Expression * rhs, char opcode) :
      left(lhs), right(rhs), op(opcode) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << op << right->toString() << ")";
    return s.str();
  }
  virtual ~OpExpression() {
    delete left;
    delete right;
  }
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) :
      OpExpression::OpExpression(lhs, rhs, '+') {}
  virtual ~PlusExpression() {}
};

class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) :
      OpExpression::OpExpression(lhs, rhs, '-') {}
  virtual ~MinusExpression() {}
};

class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) :
      OpExpression::OpExpression(lhs, rhs, '*') {}
  virtual ~TimesExpression() {}
};

class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) :
      OpExpression::OpExpression(lhs, rhs, '/') {}
  virtual ~DivExpression() {}
};
#endif

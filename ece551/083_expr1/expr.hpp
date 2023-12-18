#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <iostream>  // std
#include <sstream>   // stringstream
#include <vector>    // std::vector

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
  long number;

 public:
  NumExpression(long num) : number(num){};
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    std::string res = s.str();
    return res;
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
  Expression * left;
  Expression * right;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : left(lhs), right(rhs) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << "(" << left->toString() << "+" << right->toString() << ")";
    std::string res = s.str();
    return res;
  }
  virtual ~PlusExpression() {
    delete left;
    delete right;
  }
};

#endif

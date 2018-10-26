#include <string>
using namespace std;
#include <sstream>

class Expression
{
 public:
  virtual long evaluate() const = 0;
  virtual string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression
{
  long number;

 public:
  NumExpression(long v) : number(v) {}
  virtual string toString() const {
    stringstream num;
    num << number;
    return num.str();
  }
  virtual long evaluate() const { return number; }
};

class TempExpression : public Expression
{
 protected:
  const char theOp;
  Expression *lhs, *rhs;

 public:
  TempExpression(const char op, Expression * lhs, Expression * rhs) :
      theOp(op),
      lhs(lhs),
      rhs(rhs) {}
  virtual string toString() const {
    stringstream oper;
    oper << '(' << lhs->toString() << ' ' << theOp << ' ' << rhs->toString() << ')';
    return oper.str();
  }
  virtual ~TempExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public Expression
{
  const char theOp;
  Expression *lhs, *rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : theOp('+'), lhs(lhs), rhs(rhs){};
  virtual string toString() const {
    stringstream plus;
    plus << '(' << lhs->toString() << ' ' << theOp << ' ' << rhs->toString() << ')';
    return plus.str();
  }
  virtual long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  };
};

class MinusExpression : public TempExpression
{
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : TempExpression('-', lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
};

class TimesExpression : public TempExpression
{
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : TempExpression('*', lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
};

class DivExpression : public TempExpression
{
 public:
  DivExpression(Expression * lhs, Expression * rhs) : TempExpression('/', lhs, rhs) {}
  virtual long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
};

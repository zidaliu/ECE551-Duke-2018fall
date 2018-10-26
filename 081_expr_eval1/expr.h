#include <string>
using namespace std;
#include <sstream>

class Expression
{
 public:
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
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  };
};

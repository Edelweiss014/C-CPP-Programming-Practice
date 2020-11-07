#ifndef _EXPR_H_
#define _EXPR_H_

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <ctype.h>
#include <cstdio>
#include <cstdlib>

class Expression {
public:
    Expression() { }
    virtual ~Expression() { }
    virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
private:
    long thisNum; 
public:
    NumExpression() : thisNum(0) { }
    NumExpression(long a) : thisNum(a) { }
    NumExpression(const NumExpression & rhs) : thisNum(rhs.getNum()) { }
    ~NumExpression() { }
    long getNum() const {
        return thisNum;
    }
    virtual std::string toString() const {
        std::stringstream ss;
        ss << thisNum;
        return ss.str();
    }
};

class EvalExpression : public Expression {
private:
    Expression * lhs;
    Expression * rhs;
public:
    EvalExpression() : lhs(NULL), rhs(NULL) { }
    EvalExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) { }
    ~EvalExpression() {
        delete lhs;
        delete rhs;
    }
    virtual char getOp() const = 0;
    virtual std::string toString() const {
        std::stringstream ss;
        ss << "(" << lhs->toString() << " " << getOp() << " " << rhs->toString() << ")";
        return ss.str();
    }
};

class PlusExpression : public EvalExpression {
private:
    char op;
public:
    PlusExpression() : EvalExpression(), op('+') { }
    PlusExpression(Expression * lhs, Expression * rhs) : EvalExpression(lhs, rhs), op('+') { }
    ~PlusExpression() { }
    virtual char getOp() const {
        return op;
    }
};


#endif
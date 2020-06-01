//
// Created by israelk on 12/11/2019.
//
//#ifndef UNTITLED3_ex1_H
//#define UNTITLED3_ex1_H
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include "Expression.h"
//#include "ex1.cpp"
using namespace std;




class Variable : public Expression {
private:
    string name;
    double value;
public:
    Variable(string s, double v) : name(s), value(v){}
    virtual ~Variable() {}
    double calculate();
    Variable &operator++();
    Variable &operator--();
    Variable &operator+=(double d);
    Variable &operator-=(double d);
    Variable &operator++(int);
    Variable &operator--(int);
};

class Value : public Expression {
private:
    double val;
public:
    Value(double userVal) : val(userVal) {}
    virtual ~Value() {};
    double calculate();
};

class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* exp1) :exp(exp1) {}
    virtual ~UnaryOperator() {}
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp1) : UnaryOperator(exp1){}
    virtual ~UPlus() {}
    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp1) : UnaryOperator(exp1) {}
    virtual ~UMinus() {}
    double calculate();
};

class BinaryOperator : public Expression {
protected:
Expression *exp1;
Expression *exp2;
public:
BinaryOperator(Expression* x, Expression* p): exp1(x),exp2(p) {}
virtual ~BinaryOperator() {};
};

class Plus : public BinaryOperator {
public:
    Plus(Expression* plusL, Expression* plusR): BinaryOperator(plusL,plusR) {}
    virtual ~Plus() {}
    double calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *minusL, Expression *minusR): BinaryOperator(minusL,minusR) {}
    virtual ~Minus() {}
    double calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *mulL, Expression *mulR): BinaryOperator(mulL,mulR) {}
    virtual ~Mul() {}
    double calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *divL, Expression *divR) : BinaryOperator(divL,divR) {}
    virtual ~Div() {}
    double calculate();
};

class Interpreter {
private:
    Expression* inter;
    map<string, string> varies;
public:
    Expression *interpret(string str);
    string fromCharToString(char c);
    double calculate();
    void setVariables(string set);
    bool isNumber(string s);
    bool isValidName (string s);
    bool isOperator(string s);
};

//#endif //UNTITLED3_ex1_H

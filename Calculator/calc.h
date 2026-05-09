//
// Created by 85375 on 2025/11/23.
//

#ifndef CALCULATOR_CALC_H
#define CALCULATOR_CALC_H
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

class calc {
private :
    char* expression;   //这里为什么不能用static
    enum token{
        Value,
        Add,
        Sub,
        Mul,
        Div,
        Exp,
        O_parenthesis,
        C_parenthesis,
        Eof,
    };
    token getOperator(int &value) ; //这里传参数的作用是遇到数字时把数字传给value
    void BinaryOperator(token op , stack<int> &dataStack);
public:
    explicit calc(char * ex = {}) {
        expression = new char [strlen(ex) +1];
        strcpy(expression, ex);
    }
    ~calc() {
        delete []expression;
    }
    int result();

};




#endif //CALCULATOR_CALC_H
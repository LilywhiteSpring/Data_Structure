//
// Created by 85375 on 2025/11/23.
//
#include "calc.h"

int calc::result() {
    stack<int> dataStack;
    stack<token> tokenStack;
    int current_value;
    token current_token = getOperator(current_value),top_token;
    while (current_token != Eof) {
        switch (current_token) {
            case Value: dataStack.push(current_value) ; break;
            case O_parenthesis: tokenStack.push(current_token) ; break;
            case C_parenthesis: while (tokenStack.top() != O_parenthesis) {
                top_token = tokenStack.top() ;
                tokenStack.pop();
                BinaryOperator(top_token , dataStack);
            }
                tokenStack.pop();
                break;
                case Add: case Sub:
                while ( ! tokenStack.empty() && tokenStack.top() != O_parenthesis  ) {
                top_token = tokenStack.top();
                tokenStack.pop();
                BinaryOperator(top_token , dataStack);
            }
                tokenStack.push(current_token);
                break;
            case Mul: case Div:
                while (tokenStack.top() >= Mul && !tokenStack.empty()) {
                    top_token = tokenStack.top();
                    tokenStack.pop();
                    BinaryOperator(top_token , dataStack);
                }
                tokenStack.push(current_token);
                break;
            case Exp: tokenStack.push(current_token) ; break;
            default:;
        }
        current_token = getOperator(current_value);
    }
    while (! tokenStack.empty()) {
        top_token = tokenStack.top();
        tokenStack.pop();
        BinaryOperator(top_token, dataStack);
    }
    if (dataStack.empty()) {
        cout<<"表达式输入错误！！"<<endl;
        throw;
    }
    int result = dataStack.top();
    dataStack.pop();
    if (! dataStack.empty()) {
        cout<<""<<endl;
        throw;
    }
    cout<<"计算结果是："<<result<<endl;
    return result;
}




void calc::BinaryOperator(token op,stack<int> &dataStack) {
    if (dataStack.empty()) {
        cout<<"缺少右运算数！"<<endl;
        throw;
    }
    int back = dataStack.top() ;
    dataStack.pop();
    if (dataStack.empty()) {
        cout<<"缺少左运算数！"<<endl;
    }
    int front = dataStack.top() ;
    dataStack.pop();
    switch (op) {
        case Add: dataStack.push(front + back) ; break;
        case Sub: dataStack.push(front - back) ; break;//如果减号做负号？
        case Mul: dataStack.push(front * back) ; break;
        case Div: dataStack.push(front / back) ; break;
        {
            case Exp:
            int result = front;
            for (int i=1;i< back;++i)
                result *= front;
            dataStack.push(result);
            break;
        }
        default: throw;
    }
}



calc::token calc::getOperator(int &value) {
    if ('\0'  == *expression)
        return Eof;
    while (' ' == * expression)
        ++expression;
    if(*expression >='0' && *expression <='9') {
        value =0;
        while (*expression >='0' && *expression <='9') {
            value = 10*value + *expression - '0';
            ++expression;
        }
        return Value;
    }
    switch (*expression) {
        case '+': ++expression ;  return Add;
        case '-' : ++expression ; return Sub;
        case '*': ++expression ; return Mul;
        case '/': ++expression ; return Div;
        case '^': ++expression ; return Exp;
        case '(': ++expression ; return O_parenthesis;
        case ')': ++expression ; return C_parenthesis;
        default: throw ;
    }
}

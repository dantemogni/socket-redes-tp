#include "./headers/Calculator.h"

double Calculator::Calculate(double x, char oper, double y) {

    switch(oper)
    {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '*':
            return x * y;
        case '/':
            return x / y;
        default:
            return 0.0;
    }
}

double Calculator::Factorial(double x) {
    if (x == 0) {
        return 1;
    } else {
        return x * Factorial(x - 1);
    }
}
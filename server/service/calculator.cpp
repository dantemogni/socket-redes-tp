#include "./../headers/calculator.h"
#include "./../headers/validate.h"


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
        case '^':
            return pow(x, y);
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

string Calculator::Do(char buffer[]){
    Logger::Info("Calculando operacion ...");

    bool isValid, isFactorial;
    double result, numberA, numberB;
    char op;
    string msg;

    Validate::Do(buffer, &isValid, &isFactorial, &numberA, &numberB, &op);

    if (isValid){
        if (isFactorial){
            result = Calculator::Factorial(numberA);
            msg = to_string(numberA) + "! =" + to_string(result);
        } else {
            result = Calculator::Calculate(numberA, op, numberB);
            msg = to_string(numberA) + op + to_string(numberB) + " = " + to_string(result);
        }
    } else {
        msg = "Invalid operation";
    }

    Logger::Debug(msg);
    Logger::Info("Calculando operacion ... OK");

    return msg;
}
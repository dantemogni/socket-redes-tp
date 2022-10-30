#include "./../headers/calculator.h"
#include "./../headers/validate.h"


int Calculator::Calculate(int x, char oper, int y) {

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

int Calculator::Factorial(int x) {
    if (x == 0) {
        return 1;
    } else {
        return x * Factorial(x - 1);
    }
}

string Calculator::Do(string buffer){
    Logger::Info("Calculando operacion ...");

    bool isValid = false, isFactorial = false;
    string strNumberA, strNumberB;
    int result, numberA, numberB;
    char op;
    string msg;

    msg = Validate::Do(buffer, &isValid, &isFactorial, &strNumberA, &strNumberB, &op);

    if (isValid){
        numberA = stoi(strNumberA);

        if (isFactorial){
            result = Calculator::Factorial(numberA);
            msg = to_string(numberA) + "! = " + to_string(result);
        } else {
            numberB = stoi(strNumberB);
            result = Calculator::Calculate(numberA, op, numberB);
            msg = to_string(numberA) + op + to_string(numberB) + " = " + to_string(result);
        }
    } 

    Logger::Debug(msg);
    Logger::Info("Calculando operacion ... HECHO");

    return msg;
}
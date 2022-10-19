#include <iostream>
#include "./headers/calculator.h"

using namespace std;

double calculate(double x, char oper, double y);
double factorial(double x);

int main(int argc, char const *argv[]) 
{
    cout << "El resultado es: " << Calculator::Calculate(2.0, '+', 2.0) << endl;

    return 0;
}
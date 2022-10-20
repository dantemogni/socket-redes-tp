#pragma once

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Validate {      
  public:
    static bool Factorial(string operation, double* number);
    static bool Other(string operation, char* op, double* a, double* b);
    static bool Length(string operation);
    static void Do(char buffer[], bool* isValid, bool* isFactorial, double* numberA, double* numberB, char* op);
  private:
    static bool IsPositive(double number);
};

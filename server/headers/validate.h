#pragma once

#include <iostream>
#include <string>
#include <list>
#include "./logger.h"

using namespace std;

class Validate {      
  public:
    static bool Factorial(string operation, int* number);
    static bool Other(string operation, char* op, int* a, int* b);
    static bool Length(string operation);
    static void Do(string buffer, bool* isValid, bool* isFactorial, int* numberA, int* numberB, char* op);
  private:
    static bool IsPositive(int number);
};

#pragma once

#include <iostream>
#include <string>
#include <list>
#include "./logger.h"

using namespace std;

class Validate {      
  public:
    static bool Other(string operation, char* op, int* a, int* b);
    static bool Length(string operation);
    static string Do(string buffer, bool* isValid, bool* isFactorial, string* numberA, string* numberB, char* op);
  private:
    static bool IsPositive(int number);
    static bool HasInvalidChar(string operation, string* invalid);
    static bool Operation(string operation, char* op, string* a, string* b, string* errorMsg, bool* isFactorial);
    static bool Factorial(string operation, string* number);
    static bool HasNoOperator(string operation);
};

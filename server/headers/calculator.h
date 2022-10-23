#pragma once

#include <iostream>
#include <math.h>
#include <string>

#include "./logger.h"

using namespace std;

class Calculator {      
  public:
    static int Calculate(int x, char oper, int y);
    static int Factorial(int x);
    static string Do(string buffer);
};


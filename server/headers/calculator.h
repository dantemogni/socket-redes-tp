#pragma once

#include <iostream>
#include <math.h>
#include <string>

#include "./logger.h"

using namespace std;

class Calculator {      
  public:
    static double Calculate(double x, char oper, double y);
    static double Factorial(double x);
    static string Do(char buffer[]);
};


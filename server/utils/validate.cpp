#include "./../headers/validate.h"

using namespace std;

bool Validate::Factorial(string operation, double* number){
    // Check if the operation is factorial
    if (operation.find("!") != string::npos) {
        // Check if the operation is only factorial
        if (operation.find("!") == operation.length() - 1) {
            // Check if the number is positive
            double n = stod(operation.substr(0, operation.back()));
            if (IsPositive(n)) {
                *number = n;
                return true;
            }
        }
    }

    return false;
}

bool Validate::Other(string operation, char* op, double* a, double* b) {
    list<char> operators{'+', '-', '*', '/', '^'};

    for (char o: operators){
        size_t index = operation.find(o);

        if (index != string::npos){
            try {
                double n1 = stod(operation.substr(0, index));
                double n2 = stod(operation.substr(index + 1, operation.length()));

                if (Validate::IsPositive(n1) && Validate::IsPositive(n2)){
                    *op = o;
                    *a = n1;
                    *b = n2;
                    return true;
                }
            } catch (const std::invalid_argument& e) {
                return false;
            }
            return true;
        }
    }
    return false;
}

bool Validate::IsPositive(double number){
    return number >= 0;
}

bool Validate::Length(string operation){
    return operation.length() <= 20 && operation.length() >= 1;
}
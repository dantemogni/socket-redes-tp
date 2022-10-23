#include "./../headers/validate.h"

using namespace std;

bool Validate::Factorial(string operation, int* number){
    Logger::Info("Validando factorial ...");

    // Check if the operation is factorial
    if (operation.find("!") != string::npos) {
        // Check if the operation is only factorial
        if (operation.find("!") == operation.length() - 1) {
            // Check if the number is positive
            int n = stod(operation.substr(0, operation.back()));
            if (IsPositive(n)) {
                *number = n;
                Logger::Debug("Numero a calcular factorial: " + to_string(*number));
                return true;
            }
        }
    }

    return false;
}

bool Validate::Other(string operation, char* op, int* a, int* b) {
    Logger::Info("Validando otra operacion ...");

    list<char> operators{'+', '-', '*', '/', '^'};

    for (char o: operators){
        size_t index = operation.find(o);

        if (index != string::npos){
            try {
                int n1 = stod(operation.substr(0, index));
                int n2 = stod(operation.substr(index + 1, operation.length()));

                if (Validate::IsPositive(n1) && Validate::IsPositive(n2)){
                    *op = o;
                    *a = n1;
                    *b = n2;
                    Logger::Debug("Operation: " + operation + " | Number 1: " + to_string(n1) + " | Number 2: " + to_string(n2) + " | Operator: " + o);
                    return true;
                }
            } catch (const std::invalid_argument& e) {
                Logger::Error("Argumento invalido");
                return false;
            }
            return true;
        }
    }
    return false;
}

bool Validate::IsPositive(int number){
    return number >= 0;
}

bool Validate::Length(string operation){
    return operation.length() <= 20 && operation.length() >= 1;
}
void Validate::Do(string buffer, bool* isValid, bool* isFactorial, int* numberA, int* numberB, char* op){
    Logger::Info("Validacion general de la operacion ...");

    *isValid = true;

    if (Validate::Length(buffer)){
        if (Validate::Factorial(buffer, numberA)){
            *isFactorial = true;
            Logger::Debug("La operacion es factorial");
        } else if (Validate::Other(buffer, op, numberA, numberB)){
            *isFactorial = false;
            Logger::Debug("La operacion no es factorial");
        } else {
            *isValid = false;
            Logger::Error("Operacion invalida");

            cout << "Operación inválida" << endl;
        }
    } else {
        *isValid = false;
        Logger::Error("Operacion invalida");

        cout << "La operación debe tener entre 1 y 20 caracteres" << endl;
    }
}
#include "./../headers/validate.h"

// bool Validate::Other(string operation, char* op, int* a, int* b) {
//     Logger::Info("Validando otra operacion ...");

//     list<char> operators{'+', '-', '*', '/', '^'};

//     for (char o: operators){
//         size_t index = operation.find(o);

//         if (index != string::npos){
            
//             try {
//                 int n1 = stod(operation.substr(0, index));
//                 int n2 = stod(operation.substr(index + 1, operation.length()));

//                 if (Validate::IsPositive(n1) && Validate::IsPositive(n2)){
//                     *op = o;
//                     *a = n1;
//                     *b = n2;
//                     Logger::Debug("Operation: " + operation + " | Number 1: " + to_string(n1) + " | Number 2: " + to_string(n2) + " | Operator: " + o);
//                     return true;
//                 }
//             } catch (const std::invalid_argument& e) {
//                 Logger::Error("Argumento invalido");
//                 return false;
//             }
//             return true;
//         }
//     }
//     return false;
// }


string Validate::Do(string buffer, bool* isValid, bool* isFactorial, string* numberA, string* numberB, char* op){
    string invalid;
    string errorMsg;
    string response_msg;

    Logger::Info("Validacion general de la operacion ...");

   *isValid = true;

    if (Validate::Length(buffer)){
        // Valido si tiene un operador
        if (Validate::HasNoOperator(buffer)) {
            *isValid = false;
            return buffer;
        }

        // Valido si tiene un caracter invalido
        if (Validate::HasInvalidChar(buffer, &invalid)) {
            *isValid = false;
            fflush(stdin);
            return "No se pudo realizar la operación, se encontró un carácter no contemplado: " + invalid;
        } 

        // Valido si es factorial 
        if (Validate::Factorial(buffer, numberA)){
            *isFactorial = true;
            Logger::Debug("La operacion es factorial");
        } else if (!Validate::Operation(buffer, op, numberA, numberB, &errorMsg, isFactorial)) {
            *isValid = false;
            fflush(stdin);
            return "No se pudo realizar la operación, la operación está mal formada: " + errorMsg;
        }

        
    } else {
        *isValid = false;
        Logger::Error("Operacion invalida. La operación debe tener entre 1 y 20 caracteres");
        return "Operacion invalida. La operación debe tener entre 1 y 20 caracteres";
    }

    Logger::Info("Validacion general de la operacion ... HECHO");
    return response_msg;
}

bool Validate::IsPositive(int number){
    return number >= 0;
}

bool Validate::Length(string operation){
    return operation.length() <= 20 && operation.length() >= 1;
}


bool Validate::HasInvalidChar(string operation, string* invalid){
    Logger::Info("Validando caracteres invalidos ...");

    // Check if the operation has invalid characters
    for (char c: operation){
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != '!'){
            *invalid = c;
            Logger::Error("Caracter invalido: " + *invalid);
            return true;
        }
    }

    Logger::Info("Validando caracteres invalidos ... HECHO");
    return false;
}

bool Validate::Operation(string operation, char* op, string* n1, string* n2, string* errorMsg, bool* isFactorial){
    list<char> operators{'+', '-', '*', '/', '^', '!'};
    bool isValid = true;
    string a, b; // strings usados para mostrar en mensaje un error

    // find the operator
    for (char o: operators){
        size_t index = operation.find(o);

        if (index != string::npos){
            // get operator
            *op = o;

            // validate number 1
            string aux = operation.substr(0, index);
            if (aux.empty()){
                // si esta vacia, significa que es del tipo [operador]numero, lo cual esta mal
                a = ' ';
                isValid = false;
            } else {
                a = aux[index - 1];
                *n1 = aux;
            }

            // validate number 2
            aux = operation.substr(index + 1, operation.length());
            b = aux[0];
            if (aux.empty()) {
                isValid = false;
                b = ' ';
            } else if (*op == '!') {
                // si es factorial, el segundo numero no puede tener nada
                isValid = false;
            } else {
                *n2 = aux;
            }

            if ((b == "!") || (b == "^") || (b == "+") || (b == "-") || (b == "*") || (b == "/")) {
                a = operation[index];
                *op = operation[index+1];
                b = operation[index+2];
                isValid = false;
            }

            *errorMsg = a + *op + b;
            return isValid;
        }
    }

    return false;
}

bool Validate::Factorial(string operation, string* number){
    Logger::Info("Validando factorial ...");

    // Busca el operador del factorial
    if (operation.find("!") != string::npos) {
        // Si el operador esta al final de la operacion ...
        if (operation.find("!") == operation.length() - 1) {
            string n = operation.substr(0, operation.back());
            *number = n;
            Logger::Debug("Numero a calcular factorial: " + *number);
            return true;
        }
    }

    Logger::Info("Validando factorial ... HECHO");
    return false;
}

bool Validate::HasNoOperator(string operation){
    list<char> operators{'+', '-', '*', '/', '^', '!'};

    for (char o: operators){
        size_t index = operation.find(o);

        if (index != string::npos){
            return false;
        }
    }

    return true;
}
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    string input;

    cout << "CALCULADORA CLI APPLICATION" << endl
        << "****************************************************" << endl << endl
        << "> Menu Principal" << endl
        << "\tFormato valido: [operando][operacion][operando] | [operando][Factorial]"  << endl
        << "\tEs decir: a+b | a-b | a*b | a/b | a^b | a!" << endl << endl
        << "\tIngrese su operacion: ";
    
    cin >> input;

    cout << "El resultado es: " << input << endl;

    return 0;
}

#include "./../headers/menu.h"

void mainMenu(int socket, int socketFileDescriptor){
    string userInput;
    string operacionInput;
    char buffer[50000] = { 0 }; // buffer para recibir mensajes. Podria mejorar implementacion
    int valread;
    int intUserInput;
    int timeoutFlag = 0;

    do
    {
        cout 
            << endl 
            << "CALCULADORA - CLI APPLICATION" << endl
            << "****************************************************" << endl << endl
            << "> Menu Principal" << endl
            << "\t[ 1 ] - Realizar cálculo" << endl
            << "\t[ 2 ] - Ver registro de actividades" << endl
            << "\t[ 3 ] - Cerrar sesión" << endl << endl
            << "\tIngrese su opción: ";
    
        getline(cin, userInput);
        intUserInput = stoi(userInput);

        switch (intUserInput)
        {
        case 1:
            system("clear");
            timeoutFlag = subMenuCalcular(socket);
            system("clear");
            break;
        case 2:
            system("clear");
            send(socket, "l", 1, 0);

            // vacio el buffer
            fill(begin(buffer), end(buffer), '\0');

            valread = read(socket, buffer, sizeof(buffer));
            cout << buffer;

            break;
        case 3:
            system("clear");
            cout << "Cerrando sesión... hasta luego" << endl;
            send(socket, "q", 1, 0);
            break;
        default:
            system("clear");
            cout << "Opción inválida" << endl;
            break;
        }
    } while ((intUserInput != 3) && (timeoutFlag != 1));
}

int subMenuCalcular(int socket){
    string operacionInput;
    // char operacionInput[22];
    char buffer[5000] = { 0 };

    while(true)
    {
        cout 
            << "> Realizar cálculo" << endl
            << "\tFormato valido: [operando][operacion][operando] | [operando][Factorial]"  << endl
            << "\tEs decir: a+b | a-b | a*b | a/b | a^b | a!" << endl << endl
            << "\tEscriba 'q' o 'volver' para cancelar." << endl << endl
            << "\tIngrese su operacion: ";

        getline(cin, operacionInput);

        if(operacionInput == "q" || operacionInput == "volver"){
            break;
        }

        send(socket, operacionInput.c_str(), sizeof(operacionInput), 0);
        
        // clean buffer
        fill(begin(buffer), end(buffer), '\0');

        int valread = read(socket, buffer, 5000);

        system("clear");

        if(strcmp(buffer, "timeout") == 0){
            cout << "Cliente desconectado por el servidor. Vuelva a conectarse" << endl; 
            sleep(2);
            return EXIT_FAILURE;
        }
        cout << "RESULTADO: " << buffer << endl << endl;
    }
    return EXIT_SUCCESS;
    
}
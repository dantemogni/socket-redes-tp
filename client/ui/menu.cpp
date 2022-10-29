#include "./../headers/menu.h"

void mainMenu(int socket, int socketFileDescriptor){
    int userInput;
    string operacionInput;
    char buffer[50000] = { 0 }; // buffer para recibir mensajes. Podria mejorar implementacion
    int valread;
    
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
    
        cin >> userInput;

        switch (userInput)
        {
        case 1:
            system("clear");
            subMenuCalcular(socket);
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
            close(socketFileDescriptor);
            break;
        default:
            system("clear");
            cout << "Opción inválida" << endl;
            break;
        }
    } while (userInput != 3);
}

void subMenuCalcular(int socket){
    string operacionInput;
    char buffer[5000] = { 0 };

    while(true)
    {
        cout 
            << "> Realizar cálculo" << endl
            << "\tFormato valido: [operando][operacion][operando] | [operando][Factorial]"  << endl
            << "\tEs decir: a+b | a-b | a*b | a/b | a^b | a!" << endl << endl
            << "\tEscriba 'q' o 'volver' para cancelar." << endl << endl
            << "\tIngrese su operacion: ";

        cin >> operacionInput;
        
        if(operacionInput == "q" || operacionInput == "volver"){
            break;
        }

        send(socket, operacionInput.c_str(), operacionInput.length(), 0);
        
        // clean buffer
        fill(begin(buffer), end(buffer), '\0');

        int valread = read(socket, buffer, 5000);
        system("clear");
        cout << "RESULTADO: " << buffer << endl << endl;
    }
    
}
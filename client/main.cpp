#include <iostream>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

using namespace std;

void mainMenu(int socket, int socketFileDescriptor);
void subMenuCalcular(int socket);

int main(int argc, char const *argv[])
{
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd
         = connect(sock, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    mainMenu(sock, client_fd);
    return 0;
}

void mainMenu(int socket, int socketFileDescriptor){
    int userInput;
    string operacionInput;

    do
    {
        cout 
            << endl 
            << "CALCULADORA - CLI APPLICATION" << endl
            << "****************************************************" << endl << endl
            << "> Menu Principal" << endl
            << "\t1. Realizar cálculo" << endl
            << "\t2. Ver registro de actividades" << endl
            << "\t3. Cerrar sesión" << endl << endl
            << "\tIngrese su opción: ";
    
        cin >> userInput;

        switch (userInput)
        {
        case 1:
            system("clear");
            subMenuCalcular(socket);
            
            break;
        case 2:
            /* code */
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
    char buffer[1024] = { 0 };

    do
    {
        cout 
            << "> Realizar cálculo" << endl
            << "\tFormato valido: [operando][operacion][operando] | [operando][Factorial]"  << endl
            << "\tEs decir: a+b | a-b | a*b | a/b | a^b | a!" << endl << endl
            << "\tEscriba 'q' o 'volver' para cancelar." << endl << endl
            << "\tIngrese su operacion: ";

        cin >> operacionInput;
        send(socket, operacionInput.c_str(), operacionInput.length(), 0);

        int valread = read(socket, buffer, 1024);
        cout << "RESULTADO: " << buffer << endl;
    } while (operacionInput != "q" && operacionInput != "volver");
    
}
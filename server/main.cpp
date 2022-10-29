#include <iostream>
#include <string>
#include <list>
#include "./headers/calculator.h"
#include "./headers/validate.h"
#include "./headers/socket.h"
#include "./headers/logger.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 8080

using namespace std;

int main(int argc, char const *argv[]) {
    system("clear");

    Logger::Info("=======================================");
    Logger::Info("========== Inicia Servidor ============");
    Logger::Info("=======================================");

     // setup socket
    int port = DEFAULT_PORT, server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    // seteo el puerto segun los argumentos de la linea de comandos
    if (argc == 1) {
        Logger::Info("No se ha ingresado ningun puerto. Utilizando valor por defecto");
    } else {
        port = atoi(argv[1]);
    }

    socketSetup(port, &server_fd, address);

    // Main Server Loop
    while (true) {
        Logger::Info("Esperando conexión...");

        // Accept new connection
        if ((new_socket
            = accept(server_fd, (struct sockaddr*)&address,
                    (socklen_t*)&addrlen))
            < 0) {
            perror("accept");
            Logger::Error("Error al aceptar conexión");

            exit(EXIT_FAILURE);
        }

        Logger::Info("Conexión aceptada");

        // Connected Socket loop
        while(true) {
            string msg;

            // vacio el buffer
            fill(begin(buffer), end(buffer), '\0');

            valread = read(new_socket, buffer, 1024);

            Logger::Debug("Mensaje recibido: " + string(buffer));

            // si el mensaje es para ver logs
            if (buffer[0] == 'l') {
                Logger::Info("Enviando logs al cliente");

                msg = Logger::GetLogFileContent();
            } else if (buffer[0] == 'q') {
                Logger::Info("Cerrando conexión con el cliente");
                // closing the connected socket
                close(new_socket);
                break;
            } else {
                msg = Calculator::Do(buffer);
            }

            send(new_socket, msg.c_str(), msg.length(), 0);
        }
    
    }

    // closing the listening socket
    Logger::Info("Cerrando socket de escucha ...");
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
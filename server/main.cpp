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

using namespace std;

int main(int argc, char const *argv[]) {
    Logger::Info("=======================================");
    Logger::Info("========== Inicia Servidor ============");
    Logger::Info("=======================================");

    // setup socket
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];
 
    socketSetup(&server_fd, address);

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
        do {
            string msg;

            // vacio el buffer
            fill(begin(buffer), end(buffer), '\0');

            valread = read(new_socket, buffer, 1024);

            Logger::Debug("Mensaje recibido: " + string(buffer));

            // si el mensaje es para ver logs
            if (buffer[0] == 'l') {
                Logger::Info("Enviando logs al cliente");

                msg = Logger::GetLogFileContent();

            } else {
                 msg = Calculator::Do(buffer);
            }

            send(new_socket, msg.c_str(), msg.length(), 0);

        } while (buffer[0] != 'q');
    
        // closing the connected socket
        Logger::Info("Cerrando conexión con socket a pedido del usuario...");
        close(new_socket);
    }

    // closing the listening socket
    Logger::Info("Cerrando socket de escucha ...");
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
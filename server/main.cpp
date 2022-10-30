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

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

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

        // Aacepto la conexión
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

            // Para el timeout
            auto start = Clock::now();
            
            string msg;

            // vacio el buffer
            fill(begin(buffer), end(buffer), '\0');

            // leo el buffer
            valread = read(new_socket, buffer, 1024);

            // chequea si la duracion en mintuos es mayor a 2, si es asi, cierra la conexion
            if (chrono::duration_cast<chrono::minutes>(Clock::now() - start).count() > 2) {
                Logger::Info("Cliente desconectado por inactividad. Cerrando conexión...");
                send(new_socket, "timeout", 10, 0);
                close(new_socket);
                break;
            }

            Logger::Debug("Mensaje recibido: " + string(buffer));

            // si el mensaje es para ver logs
            if (buffer[0] == 'l') {
                Logger::Info("Enviando logs al cliente");

                msg = Logger::GetLogFileContent();
            } else if (buffer[0] == 'q') {
                Logger::Info("Cerrando conexión con el cliente");
                close(new_socket);
                break;
            } else {
                msg = Calculator::Do(buffer);
                Logger::Debug("Mensaje a enviar: " + msg);
            }

            send(new_socket, msg.c_str(), msg.length(), 0);
        }
    
    }

    // closing the listening socket
    Logger::Info("Cerrando socket de escucha ...");
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
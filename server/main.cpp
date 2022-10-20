#include <iostream>
#include <string>
#include <list>
#include "./headers/calculator.h"
#include "./headers/validate.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8009

using namespace std;

int main(int argc, char const *argv[]) {

    // Socket Setup
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
 
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
 
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Main Server Loop
    while (true) {
        if ((new_socket
            = accept(server_fd, (struct sockaddr*)&address,
                    (socklen_t*)&addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Connected Socket loop
        do {
            valread = read(new_socket, buffer, 1024);

            char op = 0;
            double a, b;
            double result;
            string msg;

            if (Validate::Length(buffer)){
                if (Validate::Factorial(buffer, &a)){
                    result = Calculator::Factorial(a);
                    msg = "El factorial de " + to_string(a) + " es: " + to_string(result);
                } else if (Validate::Other(buffer, &op, &a, &b)){
                    result = Calculator::Calculate(a, op, b);
                    msg = to_string(a) + " " + op + " " + to_string(b) + " = " + to_string(result);
                } else {
                    cout << "Operación inválida" << endl;
                }
            } else {
                cout << "La operación debe tener entre 1 y 20 caracteres" << endl;
            }
            send(new_socket, msg.c_str(), msg.length(), 0);

        } while (buffer[0] != 'q');
    
        // closing the connected socket
        close(new_socket);
    }

    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
#include <iostream>
#include <string>
#include <list>
#include "./headers/calculator.h"
#include "./headers/validate.h"
#include "./headers/socket.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;


int main(int argc, char const *argv[]) {

    // Socket Setup
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
 
    socketSetup(&server_fd, address);

    // Main Server Loop
    while (true) {
        // Accept new connection
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

            string msg = Calculator::Do(buffer);

            send(new_socket, msg.c_str(), msg.length(), 0);

        } while (buffer[0] != 'q');
    
        // closing the connected socket
        close(new_socket);
    }

    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);

    return 0;
}
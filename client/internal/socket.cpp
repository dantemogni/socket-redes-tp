#include "./../headers/socket.h"

int socketSetup(int* sock, struct sockaddr_in& serv_addr){
    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    // if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
    //     <= 0) {
    //     printf(
    //         "\nInvalid address/ Address not supported \n");
    //     return -1;
    // }

    return 0;
}
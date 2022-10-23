#include "./../headers/socket.h"

int socketSetup(int* sock, struct sockaddr_in& serv_addr){
    if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    return 0;
}
#include "./../headers/socket.h"


void socketSetup(int port, int* server_fd, struct sockaddr_in address){
    Logger::Info("Iniciando socket ... Puerto de escucha: " + to_string(port));

    int opt = 1; // 1 for true, as in enabled
    struct timeval timeout;  

    // Creating socket file descriptor
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        Logger::Error("Error al crear el socket");

        exit(EXIT_FAILURE);
    }
 
    // Configura SO_REUSEADDR SO_REUSEPORT como true
    if (setsockopt(*server_fd,
            SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT,
            &opt,
            sizeof(opt))
        ) {
        perror("setsockopt");
        Logger::Error("Error al configurar el socket (SO_REUSEADDR, SO_REUSEPORT)");

        exit(EXIT_FAILURE);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
 
    // Forcefully attaching socket to the port 8080
    if (bind(*server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        Logger::Error("Error al enlazar el socket con el puerto: " + to_string(port));

        exit(EXIT_FAILURE);
    }
    if (listen(*server_fd, 3) < 0) {
        perror("listen");

        Logger::Error("Error al escuchar en el puerto: " + to_string(port));

        exit(EXIT_FAILURE);
    }

    Logger::Info("Socket iniciado correctamente en el puerto: " + to_string(port));
}
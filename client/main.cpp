#include <iostream>
#include "./headers/menu.h"
#include "./headers/socket.h"
#define DEFAULT_PORT 8080


using namespace std;

int main(int argc, char const *argv[])
{
    system("clear");
    
    int port = DEFAULT_PORT, sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    if (argc == 1) {
        cout << "No se ha ingresado ningun puerto. Utilizando valor por defecto" << endl;
    } else {
        port = atoi(argv[1]);
    }

    // setup socket
    socketSetup(port, &sock, serv_addr);

    // connect
    while(client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "[ERROR] No se pudo conectar al servidor. Reintentando en 3 segundos ..." << endl;  
        sleep(3);
    }
    
    system("clear");

    // ui - display menu
    mainMenu(sock, client_fd);
    return 0;
}
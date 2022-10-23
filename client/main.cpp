#include <iostream>
#include "./headers/menu.h"
#include "./headers/socket.h"

using namespace std;

int main(int argc, char const *argv[])
{
    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    // setup socket
    socketSetup(&sock, serv_addr);

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
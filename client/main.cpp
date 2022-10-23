#include <iostream>
#include "./headers/menu.h"
#include "./headers/socket.h"

using namespace std;

int main(int argc, char const *argv[])
{
    cout << endl << "[INFO] Iniciando cliente ..." << endl << endl;

    int sock = 0, client_fd;
    struct sockaddr_in serv_addr;

    // setup socket
    socketSetup(&sock, serv_addr);

    // connect
    while(client_fd = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "[ERROR] No se pudo conectar al servidor. Reintentando en 3 segundos ..." << endl;  
        sleep(3);
    }


    cout << endl << "[INFO] Iniciando cliente ... OK" << endl << endl;

    // ui - display menu
    mainMenu(sock, client_fd);
    return 0;
}
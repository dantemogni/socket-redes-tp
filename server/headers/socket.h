#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8009

using namespace std;

void socketSetup(int* server_fd, struct sockaddr_in address);
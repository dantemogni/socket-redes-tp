#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include "./logger.h"

using namespace std;

void socketSetup(int port, int* server_fd, struct sockaddr_in address);

#pragma once
#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

using namespace std;

int socketSetup(int* sock, struct sockaddr_in& serv_addr);
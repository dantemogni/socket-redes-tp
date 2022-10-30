#pragma once

#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>


using namespace std;

void mainMenu(int socket, int client_fd);
int subMenuCalcular(int socket);
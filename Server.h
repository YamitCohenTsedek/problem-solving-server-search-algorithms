
#ifndef PROBLEM_SOLVING_SERVER_SERVER_H
#define PROBLEM_SOLVING_SERVER_SERVER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "ClientHandler.h"

class Server {
public:
    // Open the server to listen on the given port, and handle requests of the clients with the given client handler.
    virtual void open(int port, ClientHandler* clientHandler) = 0;
    // Stop the server.
    virtual void stop() = 0;
};

#endif // PROBLEM_SOLVING_SERVER_SERVER_H
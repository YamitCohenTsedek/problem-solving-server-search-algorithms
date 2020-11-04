
#ifndef PROBLEM_SOLVING_SERVER_CLIENTHANDLER_H
#define PROBLEM_SOLVING_SERVER_CLIENTHANDLER_H

#include "Solver.h"
#include "CacheManager.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>


// The client handler is in charge of handling the requests of the clients that connect to the server.
class ClientHandler {
public:
	/*
     * Handle a client by solving the problem he gives.
     * Return true if the solution was already in the cache, otherwise - return false.
     */
    virtual bool handleClient(int socket) = 0;

    virtual CacheManager* getCacheManager() = 0;
};

#endif // PROBLEM_SOLVING_SERVER_CLIENTHANDLER_H

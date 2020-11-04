
#ifndef PROBLEM_SOLVING_SERVER_MYPARALLELSERVER_H
#define PROBLEM_SOLVING_SERVER_MYPARALLELSERVER_H

#include "Server.h"
#include <vector>
#include <thread>

#define TIMEOUT_SEC 120

using namespace std;

// A server that handles the requests of the clients in parallel.
class MyParallelServer : public Server {

private:
	// The ID of the main socket (the socket of the server).
    int mainSocketID;

	// A vector of the parallel threads of the clients.
    std::vector<std::thread*> parallelThreads;

public:
    // Open the server to listen on the given port, and handle requests of the clients with the given client handler.
    void open(int port, ClientHandler *c);

    // Open the main thread of the server.
    void openMainThread(int socketId, ClientHandler* c);

    // Open a separate thread for the client.
    static void openClientThread(int clientSocket, ClientHandler* c);

    // Stop the server.
    void stop();
};

#endif // PROBLEM_SOLVING_SERVER_MYPARALLELSERVER_H
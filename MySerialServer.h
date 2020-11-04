
#ifndef PROBLEM_SOLVING_SERVER_MYSERIALSERVER_H
#define PROBLEM_SOLVING_SERVER_MYSERIALSERVER_H

#include "Server.h"
#include <thread>

using namespace std;

namespace server_side {

    // A server that handles the requests of the clients serially.
    class MySerialServer : public Server {
    private:
        bool* shouldStop;

		// Accept a new client and return the ID of the client socket.
		int static acceptClient(int socketID, bool* shouldStop);

    public:
        MySerialServer();

        // Open the server to listen on the given port.
        void open(int port, ClientHandler *clientHandler);

        // Start listening to clients and handle their requests with the given client handler.
        static void start(int socketID, ClientHandler *clientHandler, bool* shouldStop);

        // Stop the server.
        void stop();
    };
}

#endif // PROBLEM_SOLVING_SERVER_MYSERIALSERVER_H

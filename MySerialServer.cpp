
#include "MySerialServer.h"

using namespace server_side;

MySerialServer::MySerialServer() {
    this->shouldStop = new bool();
    *(this->shouldStop) = false;
}

// Open the server to listen on the given port.
void MySerialServer::open(int port, ClientHandler* clientHandler) {
    // First call to socket() function, to create the socket.
    int socketID = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;
    // Bind the host address using bind() function.
    if (bind(socketID, (struct sockaddr*) &serv, sizeof(serv)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    // Start listening to clients
    listen(socketID, 5);
    std::thread listenToClients(&MySerialServer::start, socketID, clientHandler, shouldStop);
}

// Accept a new client and return the ID of the client socket.
int MySerialServer::acceptClient(int socketID, bool* shouldStop) {
    int clientSocketID;
    listen(socketID, 5);
    struct sockaddr_in client;
    socklen_t clilen = sizeof(client);
    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    setsockopt(socketID, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
    clientSocketID = accept(socketID, (struct sockaddr*)&client, &clilen);
    if (clientSocketID < 0)	{
        if (errno == EWOULDBLOCK)	{
            *shouldStop = true;
        } else {
            throw ("An error occurred.");
        }
    }
    return clientSocketID;
}

// Start listening to clients and handle their requests with the given client handler.
void MySerialServer::start(int socketID, ClientHandler* clientHandler, bool* shouldStop) {
    while (!(*shouldStop)) {
        // Accept actual connection from a client.
        int clientSocketId = acceptClient(socketID, shouldStop);
        // If an error took place - continue to the next client.
        if (clientSocketId < 0) {
            continue;
        }
        // Handle the requests of the current client.
        clientHandler->handleClient(clientSocketId);
        // Close the client socket.
        close(clientSocketId);
    }
    // Close the server socket.
    close(socketID);
}

// Stop the serial server and close the system resources it used.
void MySerialServer::stop() {
    *(this->shouldStop) = true;
    delete this->shouldStop;
}

#include "MyParallelServer.h"

// Open the server to listen on the given port, and handle requests of the clients with the given client handler.
void MyParallelServer::open(int port, ClientHandler* clientHandler) {
    int serverSocketID;
    struct sockaddr_in serv_addr;
    // First call to socket() function, to create the socket.
    serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketID < 0) {
        perror("ERROR opening socket.");
        exit(1);
    }
    // Initialize the socket structure.
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    // Bind the host address using bind() function.
    if (bind(serverSocketID, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding.");
        exit(1);
    }
    // Create the main socket and the main thread of the server.
    mainSocketID = serverSocketID;
    listen(mainSocketID, SOMAXCONN);
    openMainThread(mainSocketID, clientHandler);
}

// Open the main thread of the server.
void MyParallelServer::openMainThread(int serverSocket, ClientHandler* clientHandler) {
    // A boolean member in order to know when to stop the main thread.
    bool shouldStop = false;
    // The socket of the client.
    int clientSocketID;
    /*
     * A flag that indicates whether it is the first client since we don't want to limit
     * the accepting time of the first client
     */
    bool flagFisrtClient = false;
    while (!shouldStop) {
        int clilen, cliSockfd;
        struct sockaddr_in cli_addr;
        clilen = sizeof(cli_addr);
        if (flagFisrtClient) {
            // Set the timeout of the accept.
            timeval timeout;
            timeout.tv_sec = TIMEOUT_SEC;
            timeout.tv_usec = 0;
            setsockopt(serverSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        }
        // Accept a connection from a client.
        clientSocketID = accept(serverSocket, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
        flagFisrtClient = true;
        // If an error took place:
        if (clientSocketID < 0) {
            // If it is a timeout - print it to the screen and stop the server
            if (errno == EWOULDBLOCK) {
                std::cout << "Timeout" << std::endl;
                shouldStop = true;
                continue;
            // Else - continue to the next client.
            } else {
                continue;
            }
        }
        // Add the separate thread of the client to the vector of the threads.
        parallelThreads.push_back(new std::thread(&openClientThread, clientSocketID, clientHandler));
    }
}

// Open a separate thread for the client.
void MyParallelServer::openClientThread(int clientSocketID, ClientHandler* clientHandler) {
    // Load the data from the cache manager.
    clientHandler->getCacheManager()->loadData();
    // Handle the client requests.
    if (!clientHandler->handleClient(clientSocketID)) {
        // Save the data at the end of the running if it does not exist in the cache.
        clientHandler->getCacheManager()->saveData();
    }
    // Close the client socket.
    close(clientSocketID);
}

// Stop the parallel server and close the system resources it used.
void MyParallelServer::stop() {
    for (std::vector<std::thread*>::iterator it = parallelThreads.begin(); it != parallelThreads.end(); it++) {
        (*(it))->join();
        delete(*it);
    }
    close(mainSocketID);
}
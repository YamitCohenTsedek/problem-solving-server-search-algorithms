#include "Main.h"
#include "MyClientHandler.h"
#include "CacheManager.h"
#include "FileCacheManager.h"
#include "MyParallelServer.h"
#include "Solver.h"
#include "BestFirstSearch.h"
#include "BFS.h"

using namespace boot;
using namespace server_side;

int Main::main(int port) {
    /*
     * Create the cache manager to store the solutions that have already been found.
     * In our case it is a file cache manager, which stores the solutions in a file.
     */
    CacheManager* fileCacheManager = new FileCacheManager();
    /*
     * Create the solver - in our case it is a searcher solver.
     * After performing experiments with the performance of the search algorithms,
     * it turned out that the best algorithm (that finds the shortest path) is AStar.
     */
    BestFirstSearch<Location>* aStar = new BestFirstSearch<Location>();
    Solver<Searchable<Location>*, Solution<Location>> *solver =
        new SearcherSolver<Location>(aStar);
    // Create the client handler.
    ClientHandler* clientHandler = new MyClientHandler(solver, fileCacheManager);
    // Define the server - in our case it is a parallel server.
    MyParallelServer* server = new MyParallelServer();
    // Open the server to listen on the given port, and handle the clients with the given client handler.
    server->open(port, clientHandler);
    // Stop the server.
    server->stop();
    // Delete all the dynamically allocated memory.
    delete(aStar);
    delete(solver);
    delete(fileCacheManager);
    delete(clientHandler);
    delete(server);
    return 0;
}
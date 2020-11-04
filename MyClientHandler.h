
#ifndef PROBLEM_SOLVING_SERVER_MYCLIENTHANDLER_H
#define PROBLEM_SOLVING_SERVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Location.h"
#include "Searchable.h"
#include "Searcher.h"
#include "SearchableMatrix.h"
#include "FileCacheManager.h"
#include "SearcherSolver.h"
#include "Solution.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class MyClientHandler : public ClientHandler {
private:
    CacheManager* cacheManager;

    Solver<Searchable<Location>*, Solution<Location>>* solver;

    vector<vector<State<Location>*>> searchableMatrix;

	// Read a line from the client socket.
    string readLine(int clientSocketID);

	// Split the given line by the given delimiter.
    vector<string> split(string line, char delimiter);

	// Build the matrix representation from the data.
    SearchableMatrix<Location>* buildMatrixFromData(vector<string> allInfo);

public:
    MyClientHandler(Solver<Searchable<Location>*, Solution<Location>>* s, CacheManager* cm) {
        solver = s;
        cacheManager = cm;
    }

	/*
     * Handle a client by solving the problem he gives.
     * Return true if the solution was already in the cache, otherwise - return false.
     */
	bool handleClient(int clientSocketID);

    CacheManager* getCacheManager() {
        return cacheManager;
    }

	// Delete all the dynamically allocated memory of the matrix.
    void deleteDynamicMemoryOfMatrix(SearchableMatrix<Location>* searchableMatrix);
};

#endif // PROBLEM_SOLVING_SERVER_MYCLIENTHANDLER_H

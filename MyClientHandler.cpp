
#include "MyClientHandler.h"

/*
 * Handle a client by solving the problem he gives.
 * Return true if the solution was already in the cache, otherwise - return false.
 */
bool MyClientHandler::handleClient(int clientSocketID) {
    Solution<Location> searchSolution;
    vector<string> infoFromClient;
    string currentLine = "";
    string problem = "";
    string solution = "";
    bool isInCache = false;
    currentLine = readLine(clientSocketID);
    while (currentLine != "end" && currentLine != "end\r") {
        infoFromClient.push_back(currentLine);
        problem += (currentLine + "\n");
        currentLine = readLine(clientSocketID);
    }
    SearchableMatrix<Location>* searchableMatrix = buildMatrixFromData(infoFromClient);
    // If a solution exists in the cache, take it from there.
    if (cacheManager->isSolutionExists(problem)) {
        solution = cacheManager->getSolution(problem);
        isInCache = true;
    // Else - find a solution.
    } else {
        searchSolution = solver->solve(searchableMatrix);
        solution = searchSolution.getPath();
        cacheManager->saveSolution(problem, solution);
    }
    solution += "\n";
    deleteDynamicMemoryOfMatrix(searchableMatrix);
    if (send(clientSocketID, solution.c_str(), strlen(solution.c_str()), 0) < 0) {
         perror("error with sending the message");
         exit(1);
    }
    return isInCache;
}

// Read a line from the client socket.
string MyClientHandler::readLine(int clientSocketID) {
    int n;
    char ch;
    string line = "";
    n = read(clientSocketID, &ch, 1);
    while (ch != '\n') {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        line += ch;
        n = read(clientSocketID, &ch, 1);
    }
    return line;
}

// Split the given line by the given delimiter.
vector<string> MyClientHandler::split(string line, char delimiter) {
    vector<string> results;
    stringstream s(line);
    string subStr;
    while (getline(s, subStr, delimiter)) {
        results.push_back(subStr);
    }
    return results;
}

// Build the matrix representation from the data.
SearchableMatrix<Location>* MyClientHandler::buildMatrixFromData(vector<string> infoFromClient) {
    vector<vector<State<Location>*>> matrix;
    searchableMatrix = matrix;
    int numOfLines = infoFromClient.size();
    // The last two lines represent the start state and the goal state.
    for (int i = 0; i < numOfLines - 2; i++) {
        vector<string> splitRow = split(infoFromClient[i], ',');
        vector<State<Location>*> states;
        int currentCost;
        // Create the line - a vector of states.
        for (int j = 0; j < splitRow.size(); ++j) {
            Location currentLocation = Location(i, j);
            currentCost = stoi(splitRow[j]);
            State<Location>* currentState = new State<Location>(currentLocation);
            currentState->setCost(currentCost);
            states.push_back(currentState);
        }
        searchableMatrix.push_back(states);
    }
    // The following line the represents the start state:
    vector<string> start = split(infoFromClient[numOfLines - 2], ',');
    Location startLocation = Location(stoi(start[0]), stoi(start[1]));
    State<Location>* startState = searchableMatrix[startLocation.getX()][startLocation.getY()];
	// The following line the represents the goal state:
	vector<string> goal = split(infoFromClient[numOfLines - 1], ',');
    Location goalLocation = Location(stoi(goal[0]), stoi(goal[1]));
    State<Location>* goalState = searchableMatrix[goalLocation.getX()][goalLocation.getY()];
    return new SearchableMatrix <Location>(startState, goalState, searchableMatrix);
}

// Delete all the dynamically allocated memory of the matrix.
void MyClientHandler::deleteDynamicMemoryOfMatrix(SearchableMatrix<Location>* searchableMatrix) {
    vector<vector<State<Location>*>> matrix = searchableMatrix->getMatrix();
    int numOfRows = matrix.size();
    int numOfcols = matrix[0].size();
    for (int i = 0; i < numOfRows; ++i) {
        for (int j = 0; j < numOfcols; ++j) {
            delete(matrix[i][j]);
        }
    }
    delete(searchableMatrix);
}
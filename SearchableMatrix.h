
#ifndef PROBLEM_SOLVING_SERVER_SERCHABLEMATRIX_H
#define PROBLEM_SOLVING_SERVER_SERCHABLEMATRIX_H

#include "Searchable.h"
#include "State.h"
#include "Location.h"
#include <string>

template <class T> class SearchableMatrix : public Searchable<T> {
private:
    // The start state.
    State<T>* start;

    // The goal state.
    State<T>* goal;

    // The matrix representation of all the states.
    vector<vector<State<T>*>> statesMatrix;

public:
    SearchableMatrix(State<T>* startState, State<T>* goalState, vector<vector<State<Location>*>> &matrix) {
        start = startState;
        goal = goalState;
		statesMatrix = matrix;
        int numOfRows = statesMatrix.size();
        int numOfCols = statesMatrix[0].size();
        // Find the neighbors of the states - if the cost of the state is -1, it has not neighbors.
        for (int i = 0; i < numOfRows; i++) {
            for (int j = 0; j < numOfCols; j++) {
                // Find the right neighbor.
                if (j != numOfCols - 1 && statesMatrix[i][j + 1]->getCost() > -1) {
					statesMatrix[i][j]->setRightNeighbor(statesMatrix[i][j + 1]);
                }
                // Find the left neighbor.
                if (j > 0 && statesMatrix[i][j - 1]->getCost() > -1) {
					statesMatrix[i][j]->setLeftNeighbor(statesMatrix[i][j - 1]);
                }
                // Find the up neighbor.
                if (i > 0 && statesMatrix[i-1][j]->getCost() > -1) {
					statesMatrix[i][j]->setUpNeighbor(statesMatrix[i - 1][j]);
                }
                // Find the down neighbor.
                if (i != numOfRows - 1 && matrix[i + 1][j]->getCost() > -1) {
					statesMatrix[i][j]->setDownNeighbor(statesMatrix[i + 1][j]);
                }
            }
        }

    }

    State<Location>* getInitialState() {
        return start;
    }

    State<Location>* getGoalState() {
        return goal;
    }

    vector<State<Location>*> getAllPossibleStates(State<Location>* state) {
        return state->getNeighbors();
    }

    vector<vector<State<T>*>>& getMatrix() {
        return statesMatrix;
    }
};

#endif // PROBLEM_SOLVING_SERVER_SERCHABLEMATRIX_H

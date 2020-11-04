
#ifndef PROBLEM_SOLVING_SERVER_SOLUTION_H
#define PROBLEM_SOLVING_SERVER_SOLUTION_H

#include "State.h"
#include <string>

using namespace std;

// Class solution represents a solution to a search problem (i.e. - a path from the start state to the goal state).
template <class T> class Solution {
private:
    string path = "";
    int pathWeight = 0;
    int developedVertices = 0;

public:
    void increaseNumOfDevelopedVertices() {
        ++developedVertices;
    }

    int getNumOfDevelopedVertices() {
        return developedVertices;
    }

    string getPath () {
        return path;
    }

    void setNoPath () {
        path = "";
        pathWeight = -1;
    }

    void setPath (string p) {
        path = p;
    }

    void appendPath (string side) {
        path += side;
    }

    void addSideToTheStart (string side) {

        path.insert(0, side + ", ");
    }

    void addCost (int cost) {
        pathWeight += cost;
    }

    void subtractCost (int cost) {
        pathWeight -= cost;
    }

    // Find the solution to the search problem.
    void findSolution(State<T>* currentState) {
        string currentSide = "";
        bool reachedToStart = false;
        while (!reachedToStart) {
            pathWeight += currentState->getCost();
            switch (currentState->getCameFromSide())
            {
                case Start:
                    reachedToStart = true;
                    break;
                case Right:
                    currentState = currentState->getRightNeighbor();
                    currentSide = "Left, ";
                case Left:
                    currentState = currentState->getLeftNeighbor();
                    currentSide = "Right, ";
                    break;
                case Up:
                    currentState = currentState->getUpNeighbor();
                    currentSide = "Down, ";
                    break;
                case Down:
                    currentState = currentState->getDownNeighbor();
                    currentSide = "Up, ";
                    break;
            }
            if (!reachedToStart)
                path.insert(0, currentSide);
        }
    }

    // Cut the last " ,".
    void fixTheLastSide() {
        path = path.substr(0, path.length() - 2);
    }

};

#endif // PROBLEM_SOLVING_SERVER_SOLUTION_H


#ifndef PROBLEM_SOLVING_SERVER_STATE_H
#define PROBLEM_SOLVING_SERVER_STATE_H

#include <string>
#include <vector>

using namespace std;

// An enum which represents all the possible sides of a state.
enum Side {
    Unknown = 0,
    Start = 1,
    Left = 2,
    Up = 3,
    Right = 4,
    Down = 5,
};

template <class T> class State {
private:
    // The concrete state is from type T.
    T state;
    // The cost to reach this state (will be set by a setter).
    double cost;
    // The state we came from to the current State (will be set by a setter).
    // The side of the state we came from to the current State (will be set by a setter).
    State<T>* cameFrom;
    Side cameFromSide;
    // The neighbors of the current state.
    State<T>* rightNeighbor;
    State<T>* leftNeighbor;
    State<T>* upNeighbor;
    State<T>* downNeighbor;
    // A boolean member which indicates whether the current state was visited or not.
    bool visited;

public:
    State(T state) : state(state) {
        cameFrom = nullptr;
        rightNeighbor = nullptr;
        leftNeighbor = nullptr;
        upNeighbor = nullptr;
        downNeighbor = nullptr;
        visited = false;
        cameFromSide = Unknown;
    }

    T getState(){
        return this->state;
    }

    double getCost(){
        return this->cost;
    }

    void setCost(double cost){
        this->cost=cost;
    }

    State<T>* getCameFrom(){
        return this->cameFrom;
    }

    Side getCameFromSide() {
        return cameFromSide;
    }

    bool isVisited() {
        return visited;
    }

    State<T>* getUpNeighbor() {
        return upNeighbor;
    }

    State<T>* getDownNeighbor() {
        return downNeighbor;
    }

    State<T>* getLeftNeighbor() {
        return leftNeighbor;
    }

    State<T>* getRightNeighbor() {
        return rightNeighbor;
    }

    void setCameFrom(State<T>*came){
        this->cameFrom=came;
    }

    void setRightNeighbor(State<T>* right) {
        rightNeighbor = right;
    }

    void setLeftNeighbor(State<T>* left) {
        leftNeighbor = left;
    }

    void setUpNeighbor(State<T>* up) {
        upNeighbor = up;
    }

    void setDownNeighbor(State<T>* down) {
        downNeighbor = down;
    }

    void setVisited(bool wasVisited) {
        visited = wasVisited;
    }

    void setCameFromSide(Side came) {
        cameFromSide = came;
    }

    vector<State<T>*> getNeighbors() {
        vector<State<T>*> neighbors;
        if (rightNeighbor != nullptr) {
            neighbors.push_back(rightNeighbor);
        }
        if (leftNeighbor != nullptr) {
            neighbors.push_back(leftNeighbor);
        }
        if (upNeighbor != nullptr) {
            neighbors.push_back(upNeighbor);
        }
        if (downNeighbor != nullptr) {
            neighbors.push_back(downNeighbor);
        }
        return neighbors;
    }

    /* Operators overloading */

    bool operator == (const State<T>* state) const {
        if (this->getState() == state->getState() && cost == state->cost) {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (const State<T>* state) const {
        return cost < state->getCost();
    }

    ~ State() {
    }

};

#endif // PROBLEM_SOLVING_SERVER_STATE_H
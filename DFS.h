
#ifndef PROBLEM_SOLVING_SERVER_DFS_H
#define PROBLEM_SOLVING_SERVER_DFS_H

#include "Searcher.h"
#include "Solution.h"

template <class T> class DFS : public Searcher <T> {
private:
    State<T>* goalState;

public:
    // Search a path from the start state to the goal state.
    Solution<T> search(Searchable<T> *searchable) {
        State<T>* currentState;
        State<T>* start = searchable->getInitialState();
        start->setCameFromSide(Start);
        State<T>* goal = searchable->getGoalState();
        Solution<T> searchSolution;
        vector<State<T>*> neighbors;
        queue<State<T>*> queueOfStates;
        queueOfStates.push(start);
        // Perform a recursive search.
        DFSSearch(searchSolution, start);
        searchSolution.fixTheLastSide();
        return searchSolution;
    }

    bool DFSSearch(Solution<T> &searchSolution, State<T>* state) {
        // In a case that the state is null or is already visited - return false.
        if (state == nullptr || state->isVisited()) {
            return false;
        }
        searchSolution.addCost(state->getCost());
        searchSolution.increaseNumOfDevelopedVertices();
        // In a case of reaching the goal state - return true.
        if (state == goalState) {
            return true;
        }
        state->setVisited(true);

        /* Scan the neighbors recursively to find the solution. */

        // Right neighbor
        if (state->getRightNeighbor() != nullptr && DFSSearch(searchSolution, state->getRightNeighbor())) {
            searchSolution.addSideToTheStart("Right");
            return true;
        }
        // Left neighbor
        if (state->getLeftNeighbor() != nullptr && DFSSearch(searchSolution, state->getLeftNeighbor())) {
            searchSolution.addSideToTheStart("Left");
            return true;
        }
        // Up neighbor
        if (state->getUpNeighbor() != nullptr && DFSSearch(searchSolution, state->getUpNeighbor())) {
            searchSolution.addSideToTheStart("Up");
            return true;
        }
        // Down neighbor
        if (state->getDownNeighbor() != nullptr && DFSSearch(searchSolution, state->getDownNeighbor())) {
            searchSolution.addSideToTheStart("Down");
            return true;
        }
        searchSolution.subtractCost(state->getCost());
        return false;
    }
};

#endif // PROBLEM_SOLVING_SERVER_DFS_H

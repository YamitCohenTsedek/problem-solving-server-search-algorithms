
#ifndef PROBLEM_SOLVING_SERVER_BFS_H
#define PROBLEM_SOLVING_SERVER_BFS_H

#include "SearchableMatrix.h"
#include "Searcher.h"
#include "Solution.h"
#include <queue>
#include <map>

using namespace std;

template <class T> class BFS : public Searcher<T> {
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
        // The logic of BFS algorithm is performed by a queue (FIFO).
        queueOfStates.push(start);
        // As long as the queue of the states is not empty
        while (!queueOfStates.empty()) {
            // Get the element from the front of the queue.
            currentState = queueOfStates.front();
            queueOfStates.pop();
            // In a case of reaching the goal state - break the loop.
            if (currentState == goal) break;
            /*
             * Scan all the neighbors of the current state, set the side we came from, and push
             * the neighbor to the queue.
             */
            // Right neighbor
            if (currentState->getRightNeighbor() != nullptr && currentState->getRightNeighbor()->getCameFromSide() == Unknown) {
                currentState->getRightNeighbor()->setCameFromSide(Left);
                queueOfStates.push(currentState->getRightNeighbor());
            }
            // Left neighbor
            if (currentState->getLeftNeighbor() != nullptr && currentState->getLeftNeighbor()->getCameFromSide() == Unknown) {
                currentState->getLeftNeighbor()->setCameFromSide(Right);
                queueOfStates.push(currentState->getLeftNeighbor());
            }
            // Up neighbor
            if (currentState->getUpNeighbor() != nullptr && currentState->getUpNeighbor()->getCameFromSide() == Unknown) {
                currentState->getUpNeighbor()->setCameFromSide(Down);
                queueOfStates.push(currentState->getUpNeighbor());
            }
            // Down neighbor
            if (currentState->getDownNeighbor() != nullptr && currentState->getDownNeighbor()->getCameFromSide() == Unknown) {
                currentState->getDownNeighbor()->setCameFromSide(Up);
                queueOfStates.push(currentState->getDownNeighbor());
            }
            // Increase the number of the developed vertices by 1.
            searchSolution.increaseNumOfDevelopedVertices();
        }
        // If no path exists - the solution is no path (an empty path).
        if (currentState != goal){
            searchSolution.setNoPath();
            return searchSolution;
        }
        // Find the final solution - the directions of the path.
        searchSolution.findSolution(currentState);
        // Cut the last " ,".
        searchSolution.fixTheLastSide();
        return searchSolution;
    }
};

#endif // PROBLEM_SOLVING_SERVER_BFS_H

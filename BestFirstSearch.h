
#ifndef PROBLEM_SOLVING_SERVER_BESTFIRSTSEARCH_H
#define PROBLEM_SOLVING_SERVER_BESTFIRSTSEARCH_H

#include "Searcher.h"
#include "Solution.h"
#include <queue>

// A comperator for the priority queue.
template <class T> class Compare {
public:
    bool operator() (State<T> *firstState, State<T> *secondState) {
        if (firstState->getCost() > secondState->getCost()) {
            return true;
        } else {
            return false;
        }
    }
};

template <class T> class BestFirstSearch : public Searcher<T> {
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
        /*
         * The logic of Best First Search algorithm is performed by a priority queue.
         * The comparator of the priority queue compares between the costs of the states.
         */
        priority_queue<State<T>*, std::vector<State<T>*>, Compare<T>> priorityQueue;
        searchable->getInitialState()->setCameFromSide(Start);
        priorityQueue.push(start);
        // As long as the priority queue of the states is not empty:
        while (!priorityQueue.empty()) {
            // Get the top element.
            currentState = priorityQueue.top();
            priorityQueue.pop();
            // In a case of reaching the goal state - break the loop.
            if (currentState == goal) break;
            /*
             * Scan all the neighbors of the current state, set the side we came from, and push
             * the neighbor to the priority queue.
             */
            // Right neighbor
            if (currentState->getRightNeighbor() != nullptr && currentState->getRightNeighbor()->getCameFromSide() == Unknown) {
                currentState->getRightNeighbor()->setCameFromSide(Left);
                priorityQueue.push(currentState->getRightNeighbor());
            }
            // Left neighbor
            if (currentState->getLeftNeighbor() != nullptr && currentState->getLeftNeighbor()->getCameFromSide() == Unknown) {
                currentState->getLeftNeighbor()->setCameFromSide(Right);
                priorityQueue.push(currentState->getLeftNeighbor());
            }
            // Up neighbor
            if (currentState->getUpNeighbor() != nullptr && currentState->getUpNeighbor()->getCameFromSide() == Unknown) {
                currentState->getUpNeighbor()->setCameFromSide(Down);
                priorityQueue.push(currentState->getUpNeighbor());
            }
            // Down neighbor
            if (currentState->getDownNeighbor() != nullptr && currentState->getDownNeighbor()->getCameFromSide() == Unknown) {
                currentState->getDownNeighbor()->setCameFromSide(Up);
                priorityQueue.push(currentState->getDownNeighbor());
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

#endif // PROBLEM_SOLVING_SERVER_BESTFIRSTSEARCH_H
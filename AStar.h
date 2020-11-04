
#ifndef PROBLEM_SOLVING_SERVER_ASTAR_H
#define PROBLEM_SOLVING_SERVER_ASTAR_H

#include "Searcher.h"
#include "Location.h"
#include "State.h"
#include "PriorityQueue.h"
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

template<class T> class AStar : public Searcher<T> {
public:
    // The heuristic function returns the estimated distance from the current state to the goal state.
    int heuristic(State<T>* currentState, State<T>* goalState) {
        T currentConcreteState = currentState->getState();
        T goalConcreteState = goalState->getState();
        int distance = ((abs)(currentConcreteState.getX() - goalConcreteState.getX())
        + (abs)(currentConcreteState.getY() - goalConcreteState.getY()));
        return distance;
    }

    // Search a path from the start state to the goal state.
    Solution<T> search(Searchable<T> *searchable) {
        State<T>* currentState;
        State<T>* startState = searchable->getInitialState();
        startState->setCameFromSide(Start);
        State<T>* goalState = searchable->getGoalState();
        Solution<T> searchSolution;
        string side = "";
        map<State<T>*, State<T>*> cameFrom;
        map<State<T>*, int> costs;
        PriorityQueue<State<T>*, int> priorityQueue;
        if (startState == goalState) {
            searchSolution.setPath("The start state is the goal state.\n");
            return searchSolution;
        }
        // If the start state or the goal state are blocked - there is no path.
        if (searchable->getAllPossibleStates(startState).size() == 0 ||
            searchable->getAllPossibleStates(goalState).size() == 0) {
            searchSolution.setNoPath();
            return searchSolution;
        }
        // The first element in the priority queue is the start state.
        priorityQueue.put(startState, 0);
        costs[startState] = 0;
        cameFrom[startState] = startState;
        // As long as the priority queue is not empty:
        while (!priorityQueue.empty()) {
            // Get the top element from the priority queue (the state with the cheapest cost).
            currentState = priorityQueue.get();
            // In a case of reaching the goal state - break the loop.
            if (currentState == goalState) break;
            // Scan all the neighbors of the current state.
            for (State<T> *next : currentState->getNeighbors()) {
                // Find the sum cost of the current state and the next state.
                double newCost = costs[currentState] + next->getCost();
                /*
                 * If the next state does not exist in the map of the costs, or if it exists in the map
                 * but there is a cheaper cost to reach it - update the cost of the next accordingly.
                 */
                if (costs.find(next) == costs.end() || newCost < costs[next]) {
                    costs[next] = (int)newCost;
                    // The priority is the new cost + the estimation of the heuristic function.
                    int priority = newCost + heuristic(next, goalState);
                    priorityQueue.put(next, priority);
                    // Set the cameFrom value of the next state to be the current state.
                    cameFrom[next] = currentState;
                    // Increase the number of the developed vertices by 1.
                    searchSolution.increaseNumOfDevelopedVertices();
                }
            }
        }
        // If no path exists - the solution is no path (an empty path).
        if (currentState != goalState){
            searchSolution.setNoPath();
            return searchSolution;
        }
        vector<State<T>*> states;
        // Run from the current state to the start state to update the cameFrom values and to calculate the cost.
        while (currentState != startState) {
            states.push_back(currentState);
            currentState = cameFrom[currentState];
            searchSolution.addCost(currentState->getCost());
        }
        states.push_back(startState);
        // To create the solution, reverse the states in the vector.
        reverse(states.begin(), states.end());
        // Scan the neighbors of the current state to find the right side for the path.
        for (auto iterator = states.begin(); iterator != states.end() && iterator + 1 != states.end(); iterator++) {
            // Right neighbor
            if ((*(iterator + 1))->getState().getY() > (*(iterator))->getState().getY()) {
                side = "Right, ";
            }
            // Left neighbor
            if ((*(iterator + 1))->getState().getY() < (*(iterator))->getState().getY()) {
                side = "Left, ";
            }
            // Up neighbor
            if ((*(iterator + 1))->getState().getX() < (*(iterator))->getState().getX()) {
                side = "Up, ";
            }
            // Down neighbor
            if ((*(iterator + 1))->getState().getX() > (*(iterator))->getState().getX()) {
                side = "Down, ";
            }
            // Add the chosen side to the path.
            searchSolution.appendPath(side);
        }
        // Cut the last " ,".
        searchSolution.fixTheLastSide();
        return searchSolution;
    }
};

#endif // PROBLEM_SOLVING_SERVER_ASTAR_H

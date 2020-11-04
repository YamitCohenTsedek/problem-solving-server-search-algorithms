
#ifndef PROBLEM_SOLVING_SERVER_SEARCHABLE_H
#define PROBLEM_SOLVING_SERVER_SEARCHABLE_H

#include "State.h"
#include <queue>

using namespace std;

/*
 * Class Searchable represents a search problem which contains different states,
 * and particularly an initial state and a goal state.
 */
template <class T> class Searchable {
public:
    virtual State<T>* getInitialState() = 0;

    virtual State<T>* getGoalState() = 0;

    virtual vector<State<T>*> getAllPossibleStates(State<T>*) = 0;
};

#endif // PROBLEM_SOLVING_SERVER_SEARCHABLE_H

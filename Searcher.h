
#ifndef PROBLEM_SOLVING_SERVER_SEARCHER_H
#define PROBLEM_SOLVING_SERVER_SEARCHER_H

#include "Searchable.h"
#include "Solution.h"

using namespace std;

template <class T>
class Searcher {
public:
    // Search for a solution to the searchable problem and return it.
    virtual Solution<T> search(Searchable<T> *searchable) = 0;
};

#endif //PROBLEM_SOLVING_SERVER_SEARCHER_H




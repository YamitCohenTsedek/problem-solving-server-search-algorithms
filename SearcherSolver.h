
#ifndef PROBLEM_SOLVING_SERVER_SEARCHERSOLVER_H
#define PROBLEM_SOLVING_SERVER_SEARCHERSOLVER_H

#include "Solver.h"
#include "Searcher.h"

/*
 * Adapter design pattern - SearcherSolver is an adapter class which is in charge of
 * adapting the Searcher object (the adaptee) to the Solver interface.
 */
template <class T> class SearcherSolver : public Solver <Searchable<T>*, Solution<T>> {
private:
    Searcher<T> *searcher;

public:
    SearcherSolver(Searcher<T>* s) {
        searcher = s;
    }

    // Solve the searchable problem and return the solution.
    Solution<T> solve(Searchable<T> *problem) {
        return searcher->search(problem);
    }

    ~SearcherSolver() {
        delete searcher;
    }
};

#endif // PROBLEM_SOLVING_SERVER_SEARCHERSOLVER_H

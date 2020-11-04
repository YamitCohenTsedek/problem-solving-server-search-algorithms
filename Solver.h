
#ifndef PROBLEM_SOLVING_SERVER_STATE_H_SOLVER_H
#define PROBLEM_SOLVING_SERVER_STATE_H_SOLVER_H

template <class T, class S> class Solver {
public:
    // Solve the given problem and return the solution.
    virtual S solve(T problem) = 0;
};

#endif // PROBLEM_SOLVING_SERVER_STATE_H_SOLVER_H

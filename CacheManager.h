
#ifndef PROBLEM_SOLVING_SERVER_CACHEMANAGER_H
#define PROBLEM_SOLVING_SERVER_CACHEMANAGER_H

#include <string>

using namespace std;

// The cache manager is in charge of storing the solutions that have already been found.
class CacheManager {
public:
	// Return true if the solution is in the cache, otherwise - return false.
    virtual bool isSolutionExists(string problem) = 0;

    virtual string getSolution(string problem) = 0;

    virtual void saveSolution(string problem, string solution) = 0;

    virtual void loadData() = 0;

    virtual void saveData() = 0;
};

#endif // PROBLEM_SOLVING_SERVER_CACHEMANAGER_H

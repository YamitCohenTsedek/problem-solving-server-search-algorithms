
#ifndef PROBLEM_SOLVING_SERVER_FILECHACHMANAGER_H
#define PROBLEM_SOLVING_SERVER_FILECHACHMANAGER_H

#include "CacheManager.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <mutex>
#include <vector>

#define DELIMITER '#'
#define CACHE_FILE "cacheFile.txt"

using namespace std;

// The file cache manager is in charge of storing the solutions that have already been found in a file.
class FileCacheManager : public CacheManager {
private:
    // A mutex to protect the data from concurrent access.
    mutex locker;

    // The general cache to store the solutions that have already been found.
    std::map<string, string> cache;

    // The new cache for storing solutions of problems from the current running.
    std::map<string, string> newCache;

public:
    FileCacheManager() = default;

	// Return true if the solution is in the cache, otherwise - return false.
    virtual bool isSolutionExists(string problem);

    virtual string getSolution(string problem);

    virtual void saveSolution(string problem, string solution);

    void readFromFile();

    void writeToFile();

    void loadData();

    void saveData();
};

#endif // PROBLEM_SOLVING_SERVER_FILECHACHMANAGER_H
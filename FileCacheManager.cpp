
#include "FileCacheManager.h"

// Return true if the solution is in the cache, otherwise - return false.
bool FileCacheManager::isSolutionExists(string problem) {
    return (cache.count(problem) > 0);
}

// Return the solution from the cache if it exists there, otherwise - return an empty string.
string FileCacheManager::getSolution(string problem) {
    if (isSolutionExists(problem)) {
        return cache.find(problem)->second;
    } else return "";
}

// Save the given solution of the given problem in the caches.
void FileCacheManager::saveSolution(string problem, string solution) {
    cache.insert(pair<string, string>(problem, solution));
    newCache.insert(pair<string, string>(problem, solution));
}

// Write the content of the new cache in a file.
void FileCacheManager::writeToFile() {
    locker.lock();
    ofstream file(CACHE_FILE, ios::out | ios::app | ios::ate);
    if (file.is_open()) {
        for (const auto &problem: newCache) {
            string line = problem.first + DELIMITER + problem.second + '\n';
            file << line;
        }
        file.close();
    } else {
        cout << "Error with opening the file." << endl;
    }
    locker.unlock();
}

// Read the content of the cache from a file.
void FileCacheManager::readFromFile() {
    locker.lock();
    string line = "";
    string problem = "";
    string solution = "";
    vector<string> splitLine;
    ifstream file(CACHE_FILE, ios::in);
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.find(DELIMITER) != string::npos) {
                stringstream s(line);
                string subStr;
                vector<string> splitLine;
                while (getline(s, subStr, DELIMITER)) {
                    splitLine.push_back(subStr);
                }
                problem += splitLine.at(0);
                solution = splitLine.at(1);
                cache.insert(pair<string, string>(problem, solution));
                problem = "";
            } else {
                problem += (line + "\n");
            }
        }
        file.close();
    }
    locker.unlock();
}

void FileCacheManager::loadData() {
    readFromFile();
}

void FileCacheManager::saveData() {
    writeToFile();
}
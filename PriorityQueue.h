
#ifndef PROBLEM_SOLVING_SERVER_PRIORITYQUEUE_H
#define PROBLEM_SOLVING_SERVER_PRIORITYQUEUE_H

#include "State.h"
#include "Location.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

// Class PriorityQueue wraps the priority queue of C++ and adds to it functionality for our needs.
template<class T, class Priority> class PriorityQueue {
public:
    typedef pair<Priority, T> PriorityQueueElement;
    priority_queue<PriorityQueueElement, vector<PriorityQueueElement>,
        greater<PriorityQueueElement>> elements;

    // Get the best element in the priority queue (in our case: the state that has the cheapest cost).
    T get() {
        T bestElement = elements.top().second;
        elements.pop();
        return bestElement;
    }

    // Put the given element with the given priority in the priority queue.
    void put(T element, Priority priority) {
        elements.emplace(priority, element);
    }

    // Return true if the queue is empty, otherwise - return false.
    bool empty() const {
        return elements.empty();
    }
};

#endif // PROBLEM_SOLVING_SERVER_PRIORITYQUEUE_H
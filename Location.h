
#ifndef PROBLEM_SOLVING_SERVER_LOCATION_H
#define PROBLEM_SOLVING_SERVER_LOCATION_H

#include <string>

using namespace std;

// Class Location represents a location in (x,y) coordinate space, specified in integer precision.
class Location {
private:
    int xVal, yVal;

public:
    // Create a Location object with the specified x,y coordinates.
    Location(int x, int y) : xVal(x), yVal(y) {
    }

    // Return the x-coordinate of the location.
    int getX() const {
        return xVal;
    }

    // Return the y-coordinate of the location.
    int getY() const {
        return yVal;
    }
};

#endif // PROBLEM_SOLVING_SERVER_LOCATION_H

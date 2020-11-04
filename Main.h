
#ifndef PROBLEM_SOLVING_SERVER_MAIN_H
#define PROBLEM_SOLVING_SERVER_MAIN_H

#include "MySerialServer.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>

using namespace std;

namespace boot {
    class Main {
        public:
        int main(int port);
    };
}

#endif // PROBLEM_SOLVING_SERVER_MAIN_H

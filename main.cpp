
#include "Main.h"
#include "MyClientHandler.h"

using namespace std;

int main(int argc, char* argv[]) {
    // The first and the only argument to main is the port number.
    if (argc < 2)	{
        cout << "Invalid number of arguments to main." << endl;
        return 1;
    }
    int port = atoi(argv[1]);
    boot::Main().main(port);
    return 0;
}
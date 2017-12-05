#include <iostream>
#include <cstdlib>
#include "Server.h"
using namespace std;
int main() {
    Server server(6887);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }
}
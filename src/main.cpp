#include <cstdio>
#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "Socket.h"

using namespace std;

int main(int argc, char *argv[]) {
    cout << "Start" << endl;
    ServerSocket ss(19877);
    ss.startListening();

    Socket client = ss.acceptClient();

    string sendbuf = "Client: sending data test";

    client.write(sendbuf.c_str());

    getchar();
    return 0;
}

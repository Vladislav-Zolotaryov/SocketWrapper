#include <cstdio>
#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "Socket.h"

using namespace std;

int main() {
    cout << "Start" << endl;
    ServerSocket ss(19877);
    ss.startListening();

    Socket client = ss.acceptClient();
    string sendbuf = "Client: sending data test";
    client.write(sendbuf.c_str());
	client.disconnect();

	ss.stopListening();
    return 0;
}

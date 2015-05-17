#include <cstdio>
#include <iostream>
#include <string>

#include "ServerSocket.h"
#include "Socket.h"

using namespace std;

int main() {
    cout << "Start" << endl;
	
    string hostname = "127.0.0.1";
    Socket socket(hostname.c_str(), 19877);
	socket.connectTo();
    char* result = socket.read(56);
    cout << "Result:" << endl << result << endl; 
	socket.disconnect();

    ServerSocket ss(19877);
    ss.startListening();

    Socket client = ss.acceptClient();
    string sendbuf = "Client: sending data test";
    client.write(sendbuf.c_str());
	client.disconnect();

	ss.stopListening();
    return 0;
}

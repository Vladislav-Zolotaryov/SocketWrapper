#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <iostream>
#include "SocketException.h"
#include <unistd.h>
#include "Socket.h"
#include <stdlib.h>
#include <cstring>

#ifdef _WIN32
#include <windef.h>
#include <winsock2.h>
#include <windows.h>
typedef int socklen_t;
#endif

#ifdef __gnu_linux__
#include <sys/socket.h>
#include <netinet/in.h>
typedef int SOCKET;
#endif

class ServerSocket {
public:
	ServerSocket(int port);
	~ServerSocket();
	void startListening();
	void stopListening();
	Socket acceptClient();
private:
	SOCKET clientSocket;
	SOCKET serverSocket;

	int serverPort;
	char buffer[512];

	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;

	void initServerSocket();
	void bindServerSocket();
#ifdef _WIN32
	bool wsaInitialization();
#endif
};

#endif

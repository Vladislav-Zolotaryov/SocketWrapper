#include "Socket.h"

Socket::Socket(const char* hostname, int port) {
	#ifdef _WIN32
		WSADATA wsaData;
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			throw SocketException("WSA Startup Failed");
		}
	#endif

	socketHandle = Socket::createSocketHandle();
	remoteSocketInfo = SocketHelper::createSocketInfo(hostname, port);
}

Socket::Socket(SOCKET socketHandle) {
	this->socketHandle = socketHandle;
}

Socket::~Socket() {
	disconnect();
	#ifdef _WIN32
		WSACleanup();
	#endif
}

int Socket::createSocketHandle() {
	if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		throw SocketException("Could not create socket handle");
	} 
	return socketHandle;
}

void Socket::connectTo() {
	if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0) {
		SocketHelper::closeSocket(socketHandle);
		throw SocketException("Could not connect to host");
	}
}

void Socket::disconnect() {
	SocketHelper::closeSocket(socketHandle);
}

int Socket::write(const char* message) {
	return send(socketHandle, message, strlen(message), 0);
}

char* Socket::read(const int size) {
	char* message = new char[size];
	recv(socketHandle, message, size, 0);
	return message;
}
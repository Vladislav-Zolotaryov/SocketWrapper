#include "Socket.h"

Socket::Socket(char* hostname, int port) {
	remoteSocketInfo = SocketHelper::createSocketInfo(hostname, port);
}

Socket::Socket(SOCKET socket) {
	this->socket = socket;
}

Socket::~Socket() {
	disconnect();
}

void Socket::connectTo() {
	if(connect(socket, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0) {
		SocketHelper::closeSocket(socket);
		throw SocketException("Could not connect to host");
	}
}

void Socket::disconnect() {
	SocketHelper::closeSocket(socket);
}

int Socket::write(const char* message) {
	return send(socket, message, strlen(message), 0);
}

char* Socket::read(const int size) {
	char* message = new char[size];
	recv(socket, message, size, 0);
	return message;
}
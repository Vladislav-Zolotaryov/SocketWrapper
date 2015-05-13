#include "Socket.h"

Socket::Socket(char* hostname, int port) {
	remoteSocketInfo = createSocketInfo(hostname, port);
}

Socket::Socket(int socket) {
	this->socket = socket;
}

Socket::~Socket() {
	disconnect();
}

void Socket::connectTo() {
	if(connect(socket, (struct sockaddr *)&remoteSocketInfo, sizeof(sockaddr_in)) < 0) {
	   close(socket);
	   throw SocketException("Could not connect to host");
	}
}

void Socket::disconnect() {
	close(socket);
}

int Socket::write(const char* message) {
	return send(socket, message, strlen(message), 0);
}

char* Socket::read(int size) {
	char* message = new char[size];
	recv(socket, message, size, 0);
	return message;
}

sockaddr_in Socket::createSocketInfo(char* hostname, int port) {
	clearSocketInfo();
	struct hostent *hPtr;
	if((hPtr = gethostbyname(hostname)) == NULL) {
	   throw SocketException("System DNS name resolution not configured properly");
	}
	memcpy((char *)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
	remoteSocketInfo.sin_family = AF_INET;
	remoteSocketInfo.sin_port = htons((u_short)port);
}

void Socket::clearSocketInfo() {
	bzero(&remoteSocketInfo, sizeof(sockaddr_in));	
}

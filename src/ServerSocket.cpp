#include "ServerSocket.h"

ServerSocket::ServerSocket(int port) {
	if (port <= 0) {
		throw SocketException("Invalid port");
	}
	serverPort = port;
	initServerSocket();
	bindServerSocket();
}

Socket ServerSocket::acceptClient() {
	SOCKET client;
	socklen_t length;

	length = sizeof(serverAddress);
	client = accept(serverSocket, (struct sockaddr *) &serverAddress, &length);
	return Socket(client);
}

void ServerSocket::startListening() {
	int socketListeningResult = listen(serverSocket, SOMAXCONN);

	if (socketListeningResult < 0) {
		throw SocketException("Listening failed, error: " + socketListeningResult);
	}
}

void ServerSocket::stopListening() {
	SocketHelper::closeSocket(serverSocket);

#ifdef _WIN32
	WSACleanup();
#endif
}

#ifdef _WIN32
bool ServerSocket::wsaInitialization() {
	WSADATA wsaData;
	WORD version;
	int error;

	version = MAKEWORD(2, 0);

	error = WSAStartup(version, &wsaData);
	if (error != 0) {
		throw SocketException("WSA startup failed, error: " + error);
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 0) {
		throw SocketException("Invalid WSA data version");
	}
	return true;
}
#endif

void ServerSocket::initServerSocket() {
#ifdef _WIN32
	wsaInitialization();
#endif
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (serverSocket < 0) {
		throw SocketException("Socket opening error");
	}

	memset(&serverAddress, 0, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(serverPort);
}

void ServerSocket::bindServerSocket() {
	if (bind(serverSocket, (struct sockaddr *) &serverAddress,
		sizeof(serverAddress)) < 0) {
		throw SocketException("Socket binding error");
	}
}

ServerSocket::~ServerSocket() {
	stopListening();
}

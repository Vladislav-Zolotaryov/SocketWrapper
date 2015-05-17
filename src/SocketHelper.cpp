#include "SocketHelper.h"

void SocketHelper::closeSocket(SOCKET socket) {
#ifdef _WIN32
	closesocket(socket);
#else
	close(socket);
#endif
}

sockaddr_in SocketHelper::createSocketInfo(const char* hostname, int port) {
#ifdef _WIN32
	struct sockaddr_in remoteSocketInfo;
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	const char* portStr = std::to_string(port).c_str();

	DWORD dwRetval = getaddrinfo(hostname, portStr, &hints, &result);
	if (dwRetval != 0) {
		throw SocketException("System DNS name resolution not configured properly");
	}

	remoteSocketInfo = *(struct sockaddr_in *) result->ai_addr;
	remoteSocketInfo.sin_family = AF_INET;
	remoteSocketInfo.sin_port = htons((u_short)port);

	freeaddrinfo(result);

	return remoteSocketInfo;
#else	
	struct sockaddr_in remoteSocketInfo;
	struct hostent *hPtr;

	memset(&remoteSocketInfo, 0, sizeof(sockaddr_in));

	if((hPtr = gethostbyname(hostname)) == NULL) {
		throw SocketException("System DNS name resolution not configured properly");
	}
	memcpy((char *)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
	remoteSocketInfo.sin_family = AF_INET;
	remoteSocketInfo.sin_port = htons((u_short)port);

	return remoteSocketInfo;
#endif
}
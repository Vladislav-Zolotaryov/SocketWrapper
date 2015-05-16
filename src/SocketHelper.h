#ifndef SOCKET_HELPER_H
#define SOCKET_HELPER_H

	#include "SocketException.h"

	#ifdef _WIN32
		#pragma comment(lib, "Ws2_32.lib")
		#include <io.h>
		#include <winsock2.h>
		#include <ws2tcpip.h>
	#else
		#include <sys/socket.h>
		typedef int SOCKET;
	#endif

	class SocketHelper {
		public:
			static void SocketHelper::closeSocket(SOCKET socket);
			static sockaddr_in SocketHelper::createSocketInfo(char* hostname, int port);
	};

#endif
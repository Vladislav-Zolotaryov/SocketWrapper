#ifndef SOCKET_HELPER_H
#define SOCKET_HELPER_H

	#include "SocketException.h"
        #include <string.h>
	
	#ifdef _WIN32
		#pragma comment(lib, "Ws2_32.lib")
		#include <io.h>
		#include <winsock2.h>
		#include <ws2tcpip.h>
	#else
                #include <netdb.h>
		#include <unistd.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		typedef int SOCKET;
	#endif

	class SocketHelper {
		public:
			static void closeSocket(SOCKET socket);
			static sockaddr_in createSocketInfo(const char* hostname, int port);
	};

#endif
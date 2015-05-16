#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

	#include "SocketException.h"
	#include "SocketHelper.h"
	#include "Socket.h"
	#include <iostream>
	#include <stdlib.h>
	#include <cstring>

	#ifdef _WIN32
		#pragma comment(lib, "Ws2_32.lib")
		#include <io.h>
		#include <windef.h>
		#include <winsock2.h>
		#include <windows.h>
		typedef int socklen_t;
	#else
		#include <unistd.h>
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
			SOCKET serverSocket;
			int serverPort;
			struct sockaddr_in serverAddress;

			void initServerSocket();
			void bindServerSocket();
		#ifdef _WIN32
			bool wsaInitialization();
		#endif
	};

#endif

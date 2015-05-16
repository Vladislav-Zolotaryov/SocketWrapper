#ifndef SOCKET_H
#define SOCKET_H

    #include "SocketException.h"
	#include "SocketHelper.h"
    #include <cstring> 
    
	#ifdef _WIN32
		#pragma comment(lib, "Ws2_32.lib")
		#include <winsock2.h>
		#include <windows.h>
		#include <io.h>
		typedef int socklen_t;
	#else
		#include <netdb.h>
		#include <unistd.h>
		#include <sys/socket.h>
		#include <netinet/in.h>
		typedef int SOCKET;
	#endif

	class Socket {
		public:
			Socket(char* hostname, int port);
			Socket(SOCKET socket);
			~Socket();

			void connectTo();
			void disconnect();

			int write(const char* message);
			char* read(int size);
		private:
			sockaddr_in createSocketInfo(char* hostname, int port);
			void clearSocketInfo();
			SOCKET socket;
			struct sockaddr_in remoteSocketInfo;
	};

#endif

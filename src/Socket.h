#ifndef SOCKET_H
#define SOCKET_H

    #include "SocketException.h"

    #include <netdb.h>
    #include <cstring>
    #include <unistd.h>
    
	#ifdef _WIN32
	#include <winsock2.h>
	#include <windows.h>
	typedef int socklen_t;
	#endif

	#ifdef __gnu_linux__
	#include <sys/socket.h>
	#include <netinet/in.h>
	typedef int SOCKET;
	#endif

	class Socket {
		public:
			Socket(char* hostname, int port);
			Socket(int socket);
			~Socket();

			void connectTo();
			void disconnect();

			int write(const char* message);
			char* read(int size);
		private:
			sockaddr_in createSocketInfo(char* hostname, int port);
			void clearSocketInfo();
			int socket;
			struct sockaddr_in remoteSocketInfo;
	};

#endif

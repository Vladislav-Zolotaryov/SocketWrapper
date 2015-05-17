#ifndef SOCKET_EXCEPTION_H
#define SOCKET_EXCEPTION_H

#include <string>
#include <exception> 

class SocketException : public std::exception {
public:
	SocketException(std::string errorMsg) : msg(errorMsg) {	};
	~SocketException() throw () {};
	const char* what() const throw () { return msg.c_str(); };
private:
	std::string msg;
};

#endif

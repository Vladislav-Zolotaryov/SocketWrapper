cmake_minimum_required (VERSION 2.6)
project (SocketWrapper)

set (main
    main.cpp
    
    ServerSocket.h
    ServerSocket.cpp
    
    Socket.h
    Socket.cpp
    
    SocketException.h

    SocketHelper.h
    SocketHelper.cpp
)

add_executable(SocketWrapper ${main})
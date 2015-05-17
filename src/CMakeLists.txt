cmake_minimum_required (VERSION 2.6)
project (SocketWrapper)

set (main   
    SocketException.h

    Socket.h
    Socket.cpp

    ServerSocket.h
    ServerSocket.cpp      

    SocketHelper.h
    SocketHelper.cpp

    main.cpp
)

add_executable(SocketWrapper ${main})
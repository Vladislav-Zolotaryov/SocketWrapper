cmake_minimum_required (VERSION 2.6)
project (SocketWrapper)

set (SocketWrapper_VERSION_MAJOR 1)
set (SocketWrapper_VERSION_MINOR 0)

set (main
    main.cpp
    
    ServerSocket.h
    ServerSocket.cpp
    
    Socket.h
    Socket.cpp
    
    SocketException.h
)

configure_file (
  "${PROJECT_SOURCE_DIR}/main.h.in"
  "${PROJECT_BINARY_DIR}/main.h"
)

include_directories("${PROJECT_BINARY_DIR}")

add_executable(SocketWrapper ${main})
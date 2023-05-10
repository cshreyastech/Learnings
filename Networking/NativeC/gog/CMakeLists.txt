# SPECIFY THE MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 2.8.12)


# SPECIFY YOUR PROJECT NAME
PROJECT(SocketProgramming)


# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(OpenGL_LIBS
  PRIVATE glfw 
  PRIVATE GLU 
  PRIVATE GL 
  PRIVATE Xrandr 
  # PRIVATE Xxf86vm 
  PRIVATE Xi 
  PRIVATE Xinerama 
  PRIVATE X11 
  PRIVATE rt 
  PRIVATE dl
  pthread
  PRIVATE GLEW
  )

include_directories( 
  include
  )

ADD_EXECUTABLE(tcp_server_pass_structure 
    src/socket_server.cpp
    src/tcp_server_pass_structure.cpp
  )

# TARGET_LINK_LIBRARIES(tcp_server_pass_structure  OpenGL_LIBS)

ADD_EXECUTABLE(tcp_client_pass_structure 
    src/socket_client.cpp
    src/tcp_client_pass_structure.cpp
  )

# TARGET_LINK_LIBRARIES(tcp_client_pass_structure  OpenGL_LIBS)
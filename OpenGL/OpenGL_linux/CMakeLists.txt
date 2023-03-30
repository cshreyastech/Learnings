# SPECIFY THE MINIMUM VERSION OF CMAKE REQUIRED
cmake_minimum_required(VERSION 2.8.12)


# SPECIFY YOUR PROJECT NAME
PROJECT(OpenGLApp)


# Enable C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


# INCLUDE OPENCV DIRECTORIES
include_directories( 
#  include
  )




  ADD_EXECUTABLE(${PROJECT_NAME} 
    src/Application.cpp)

  #Set Linker flags
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
  PRIVATE glfw 
  PRIVATE GLU 
  PRIVATE GL 
  # PRIVATE Xrandr 
  # PRIVATE Xxf86vm 
  # PRIVATE Xi 
  # PRIVATE Xinerama 
  # PRIVATE X11 
  # PRIVATE rt 
  # PRIVATE dl
  )





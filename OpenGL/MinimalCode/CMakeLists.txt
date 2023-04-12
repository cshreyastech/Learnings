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
  src
  )

set(target_libraries
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

ADD_EXECUTABLE(01_hello_window
  src/vendor/glad/glad.c
  src/01-hello_window.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(01_hello_window ${target_libraries})


ADD_EXECUTABLE(02_hello_triange 
  src/vendor/glad/glad.c
  src/02-hello_triangle.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_hello_triange ${target_libraries})


ADD_EXECUTABLE(02_1_hello_trianges 
  src/vendor/glad/glad.c
  src/02_1-hello_triangles.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_1_hello_trianges ${target_libraries})

ADD_EXECUTABLE(02_2-two_triangles_diff_objs 
  src/vendor/glad/glad.c
  src/02_2-two_triangles_diff_objs.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_2-two_triangles_diff_objs ${target_libraries})


ADD_EXECUTABLE(02_3-two_triangles_two_objs_two_shaders 
  src/vendor/glad/glad.c
  src/02_3-two_triangles_two_objs_two_shaders.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_3-two_triangles_two_objs_two_shaders ${target_libraries})


ADD_EXECUTABLE(03_1-shaders 
  src/vendor/glad/glad.c
  src/03_1-shaders.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_1-shaders ${target_libraries})


ADD_EXECUTABLE(03_2-uniform 
  src/vendor/glad/glad.c
  src/03_2-uniform.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_2-uniform ${target_libraries})

ADD_EXECUTABLE(03_3-more_attributes 
  src/vendor/glad/glad.c
  src/03_3-more_attributes.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_3-more_attributes ${target_libraries})

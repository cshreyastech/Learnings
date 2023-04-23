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
  src/core
  src/tbd
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

ADD_EXECUTABLE(03_4-using_shader_class 
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/03_4-using_shader_class.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_4-using_shader_class ${target_libraries})


ADD_EXECUTABLE(04_1-texture
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/04_1-texture.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_1-texture ${target_libraries})


ADD_EXECUTABLE(04_2-multiple_textures
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/04_2-multiple_textures.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_2-multiple_textures ${target_libraries})


ADD_EXECUTABLE(04_ex-2
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/04_ex-2.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-2 ${target_libraries})

ADD_EXECUTABLE(04_ex-3
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/04_ex-3.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-3 ${target_libraries})


ADD_EXECUTABLE(04_ex-4
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/04_ex-4.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-4 ${target_libraries})



ADD_EXECUTABLE(04_3-dynamic-textures
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/core/Renderer.cpp
  src/04_3-dynamic_textures.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_3-dynamic-textures ${target_libraries})

ADD_EXECUTABLE(10_1-framebuffer_tbd
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c

  src/tbd/10_1-framebuffer_V2.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(10_1-framebuffer_tbd ${target_libraries})


ADD_EXECUTABLE(frame_publisher
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c

  src/tbd/client_server/client/frame_publisher.cpp
  src/tbd/client_server/client/socket_client.cpp
  
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(frame_publisher ${target_libraries})

ADD_EXECUTABLE(frame_receiver
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c

  src/tbd/client_server/server/frame_receiver2.cpp
  src/tbd/client_server/server/socket_server.cpp
  
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(frame_receiver ${target_libraries})
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
  src/01-GettingStarted/tbd
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
  PRIVATE z
  )

ADD_EXECUTABLE(01_hello_window
  src/vendor/glad/glad.c
  src/01-GettingStarted/01-CreatingWindow/01-hello_window.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(01_hello_window ${target_libraries})


ADD_EXECUTABLE(02_hello_triange 
  src/vendor/glad/glad.c
  src/01-GettingStarted/02-CreatingTriange/02-hello_triangle.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_hello_triange ${target_libraries})


ADD_EXECUTABLE(02_1_hello_trianges 
  src/vendor/glad/glad.c
  src/01-GettingStarted/02-CreatingTriange/02_1-hello_triangles.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_1_hello_trianges ${target_libraries})

ADD_EXECUTABLE(02_2-two_triangles_diff_objs 
  src/vendor/glad/glad.c
  src/01-GettingStarted/02-CreatingTriange/02_2-two_triangles_diff_objs.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_2-two_triangles_diff_objs ${target_libraries})


ADD_EXECUTABLE(02_3-two_triangles_two_objs_two_shaders 
  src/vendor/glad/glad.c
  src/01-GettingStarted/02-CreatingTriange/02_3-two_triangles_two_objs_two_shaders.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(02_3-two_triangles_two_objs_two_shaders ${target_libraries})


ADD_EXECUTABLE(03_1-shaders 
  src/vendor/glad/glad.c
  src/01-GettingStarted/03-Shaders/03_1-shaders.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_1-shaders ${target_libraries})


ADD_EXECUTABLE(03_2-uniform 
  src/vendor/glad/glad.c
  src/01-GettingStarted/03-Shaders/03_2-uniform.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_2-uniform ${target_libraries})

ADD_EXECUTABLE(03_3-more_attributes 
  src/vendor/glad/glad.c
  src/01-GettingStarted/03-Shaders/03_3-more_attributes.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_3-more_attributes ${target_libraries})

ADD_EXECUTABLE(03_4-using_shader_class 
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/03-Shaders/03_4-using_shader_class.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(03_4-using_shader_class ${target_libraries})


ADD_EXECUTABLE(04_1-texture
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_1-texture.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_1-texture ${target_libraries})


ADD_EXECUTABLE(04_2-multiple_textures
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_2-multiple_textures.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_2-multiple_textures ${target_libraries})


ADD_EXECUTABLE(04_ex-2
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_ex-2.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-2 ${target_libraries})

ADD_EXECUTABLE(04_ex-3
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_ex-3.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-3 ${target_libraries})


ADD_EXECUTABLE(04_ex-4
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_ex-4.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_ex-4 ${target_libraries})



ADD_EXECUTABLE(04_3-dynamic-textures
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/core/Renderer.cpp
  src/01-GettingStarted/04-Textures/04_3-dynamic_textures.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_3-dynamic-textures ${target_libraries})

ADD_EXECUTABLE(04_4-only_texture
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_4-only_texture.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_4-only_texture ${target_libraries})

ADD_EXECUTABLE(04_5-only_texture_dynamic
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/04-Textures/04_5-only_texture_dynamic.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(04_5-only_texture_dynamic ${target_libraries})

ADD_EXECUTABLE(05_1-transformation
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/05-Transformation/05_1-transformation.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(05_1-transformation ${target_libraries})

ADD_EXECUTABLE(05_2-transformations
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/05-Transformation/05_2-transformations.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(05_2-transformations ${target_libraries})

ADD_EXECUTABLE(05_ex-2
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/05-Transformation/05_ex-2.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(05_ex-2 ${target_libraries})

ADD_EXECUTABLE(06_1-mvp1
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_1-mvp1.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_1-mvp1 ${target_libraries})

ADD_EXECUTABLE(06_2-3d
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_2-3d.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_2-3d ${target_libraries})

ADD_EXECUTABLE(06_3-more_cubes
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_3-more_cubes.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_3-more_cubes ${target_libraries})

ADD_EXECUTABLE(06_ex-3
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_ex-3.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_ex-3 ${target_libraries})


ADD_EXECUTABLE(06_4-just_cube
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_4-just_cube.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_4-just_cube ${target_libraries})

ADD_EXECUTABLE(06_5-just_cube_ebo
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_5-just_cube_ebo.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_5-just_cube_ebo ${target_libraries})

ADD_EXECUTABLE(06_6-just_cubes_ebo
  src/vendor/stb_image/stb_image.cpp
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/06-CoordinateSystems/06_6-just_cubes_ebo.cpp
  )

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(06_6-just_cubes_ebo ${target_libraries})

find_package(ZLIB)

ADD_EXECUTABLE(point_cloud_server
  src/vendor/glad/glad.c
  src/core/Shader.cpp
  src/01-GettingStarted/networking/server/src/socket_server.cpp
  src/01-GettingStarted/networking/server/src/point_cloud_server.cpp
  )

target_include_directories(point_cloud_server
  PRIVATE src/01-GettingStarted/networking/server/include)

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(point_cloud_server ${target_libraries} ZLIB::ZLIB)


ADD_EXECUTABLE(point_cloud_client
  src/01-GettingStarted/networking/client/src/myzlib.cpp
  src/01-GettingStarted/networking/client/src/socket_client.cpp
  src/01-GettingStarted/networking/client/src/point_cloud_client.cpp
  )

target_include_directories(point_cloud_client
  PRIVATE src/01-GettingStarted/networking/client/include)

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
TARGET_LINK_LIBRARIES(point_cloud_client ${target_libraries} ZLIB::ZLIB)
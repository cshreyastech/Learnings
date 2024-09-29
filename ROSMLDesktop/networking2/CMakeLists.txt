cmake_minimum_required(VERSION 3.0.0)

# SPECIFY YOUR PROJECT NAME
PROJECT(networking2)


find_package(ZLIB)

set(target_common_libraries
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
  PRIVATE ZLIB::ZLIB
  )


#######################
set(server_project server_app)

set(SERVER_HEADER_DIR
  server/include
  server/vendor
  server/core
)

set(SERVER_SRC_FILES
  server/vendor/glad/glad.c
  server/core/Shader.cpp
  server/src/socket_server.cpp
  server/src/zlib_compression.cpp
  server/src/point_cloud_server.cpp
)

ADD_EXECUTABLE(${server_project}
${SERVER_SRC_FILES}
)

# target_precompile_headers(${project_app} PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include/PCH/pch.h)

target_include_directories(${server_project}
  # PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include
  PRIVATE ${SERVER_HEADER_DIR}
)
target_link_libraries(${server_project} ${target_common_libraries} )

set_target_properties(${server_project} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)

#######################

set(CLIENT_HEADER_DIR
  client/include
)

set(CLIENT_SRC_FILES
  client/src/point_cloud_client.cpp
  client/src/socket_client.cpp
  client/src/zlib_compression.cpp
)

set(client_project client_app)


ADD_EXECUTABLE(${client_project}
${CLIENT_SRC_FILES}
)


# target_precompile_headers(${project_app} PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include/PCH/pch.h)

target_include_directories(${client_project}
  # PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include
  PRIVATE ${CLIENT_HEADER_DIR}
)
target_link_libraries(${client_project} ${target_common_libraries} )

set_target_properties(${client_project} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)


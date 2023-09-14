# https://www.youtube.com/watch?v=2hNdkYInj4g

cmake_minimum_required(VERSION 3.5)
project(gl_eye_tracking5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++2a -DMINIGLOG=ON")

set(ros_ml_client_header_dir "${PROJECT_SOURCE_DIR}/05-ros_ml/ros_ml_client/include")

set(ros_ml_client 05-ros_ml_client)
add_executable(${ros_ml_client}
  src/gl_eye_tracking/main.cpp
  src/gl_eye_tracking/ros_ml_client.cpp

  src/core/game_engine.cpp
  )
  
target_include_directories(${ros_ml_client} 
  PRIVATE include
)

# target_link_libraries(${ros_ml_client} ${target_common_libraries})
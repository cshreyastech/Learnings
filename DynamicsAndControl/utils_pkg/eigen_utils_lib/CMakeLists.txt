cmake_minimum_required(VERSION 3.0.0)
project(eigen_utils_lib)

set(lib_name ${PROJECT_NAME})

add_library(${lib_name} 
  src/eigen_utils.cpp
)

target_precompile_headers(${lib_name} 
  PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h
)

target_include_directories(${lib_name} 
  PRIVATE include
  PRIVATE ${eigen_utils_lib_SOURCE_DIR}/include
)

target_link_libraries(${lib_name} 
  PRIVATE ${PYTHON38_LIBRARY})

set_target_properties(${lib_name} PROPERTIES
  CXX_STANDARD 20  # or the C++ standard you are using
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)


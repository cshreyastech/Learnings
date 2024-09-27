project(utils_test)

## Declare a C++ library
set(app_name eigen_${PROJECT_NAME})

add_executable(${app_name} 
  src/eigen_utils_test.cpp
)

target_include_directories(${app_name} 
  # PRIVATE include
  PRIVATE ${eigen_utils_lib_SOURCE_DIR}/include
)

target_link_libraries(${app_name} 
  PRIVATE eigen_utils_lib
)

set_target_properties(${app_name} PROPERTIES
  CXX_STANDARD 20  # or the C++ standard you are using
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

target_compile_options(${app_name} PRIVATE -O3)
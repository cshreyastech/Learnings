cmake_minimum_required(VERSION 3.0.0)
project(TheFiniteElementMethodCPP)

# set(HEADER_DIR
#   include
# )

set(SRC_FILES
  src/matplotlibtest.cpp
)

set(project_app matplotlibtest_app)

ADD_EXECUTABLE(${project_app}
  ${SRC_FILES}
)

# target_precompile_headers(${project_app} PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include/PCH/pch.h)
target_precompile_headers(${project_app} PRIVATE ${CMAKE_SOURCE_DIR}/external/matplotlibcpp/include/matplotlibcpp/matplotlibcpp.h)


target_include_directories(${project_app}
  # PRIVATE ${CMAKE_SOURCE_DIR}/PCH/include
  # PRIVATE ${HEADER_DIR}
  PRIVATE ${Python3_INCLUDE_DIRS}
  PRIVATE ${matplotlibcpp_INCLUDE_DIR}
  PRIVATE include
)

target_link_libraries(${project_app} ${Python3_LIBRARY_RELEASE})

set_target_properties(${project_app} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
)
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

target_precompile_headers(${project_app} PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h)

target_include_directories(${project_app}
  PRIVATE include
)

target_link_libraries(${project_app} ${PYTHON38_LIBRARY})

set_target_properties(${project_app} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
)
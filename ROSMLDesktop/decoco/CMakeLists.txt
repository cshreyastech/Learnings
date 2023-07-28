project(decoco)
cmake_minimum_required(VERSION 3.0.0)

find_package(ZLIB)

set(HEADER_DIR
  include
  src
)

set(SRC_FILES
  src/zlib/adler32.cpp
  src/zlib/crc32.cpp
  src/zlib/deflate.cpp
  src/zlib/inffast.cpp
  src/zlib/inflate.cpp
  src/zlib/inftrees.cpp
  src/zlib/trees.cpp
  src/zlib/zutil.cpp

  src/shared.cpp
  src/zlib.cpp
)

set(project_lib ${PROJECT_NAME}_lib)


add_library(${project_lib}
${SRC_FILES}
)

target_include_directories(${project_lib}
  PUBLIC ${HEADER_DIR}
)

target_link_libraries(${project_lib} ZLIB::ZLIB)

set_target_properties(${project_lib} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
)
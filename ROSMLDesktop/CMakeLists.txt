cmake_minimum_required(VERSION 3.0.0)
project(ROSMLDesktop)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)

# add_subdirectory(decoco)
# add_subdirectory(networking2)
# add_subdirectory(networking3_no_compress)

<<<<<<< HEAD
set(SNAPPY_BUILD_TESTS OFF CACHE BOOL "")
set(SNAPPY_BUILD_BENCHMARKS OFF CACHE BOOL "")
=======

set(SNAPPY_BUILD_BENCHMARKS OFF CACHE BOOL "")
set(SNAPPY_BUILD_TESTS OFF CACHE BOOL "")
>>>>>>> fcc47d7821e17c2d2344738ff168683784d024be

add_subdirectory(ext/snappy)
# add_subdirectory(networking4)
add_subdirectory(networking5_udp)
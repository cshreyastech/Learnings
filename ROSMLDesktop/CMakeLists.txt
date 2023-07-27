cmake_minimum_required(VERSION 3.0.0)
project(ROSMLDesktop)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)

add_subdirectory(decoco)
add_subdirectory(networking)

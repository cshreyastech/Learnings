cmake_minimum_required(VERSION 3.0.0)
project(DynamicsAndControl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)


# add_subdirectory(external)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
find_package(matplotlibcpp REQUIRED)


add_subdirectory(GoodVibrationsWithFreeball)
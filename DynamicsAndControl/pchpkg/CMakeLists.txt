cmake_minimum_required(VERSION 3.0.0)
project(PCH)

add_subdirectory(external/eigen)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(PCH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)


find_package(Python38 REQUIRED)
find_package(matplotlibcpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(pch REQUIRED)


# get_target_property(eigen_inc_dir Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)


# include_directories(
#   # ${matplotlibcpp_INCLUDE_DIR}
#   ${PYTHON38_INCLUDE_DIR}
#   ${eigen_utils_lib_SOURCE_DIR}/include
#   ${pch_INCLUDE_DIR}
# )
cmake_minimum_required(VERSION 3.0.0)
project(DynamicsAndControl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)

add_subdirectory(pchpkg)

# get_target_property(eigen_inc_dir Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)


include_directories(
  ${matplotlibcpp_INCLUDE_DIR}
  ${PYTHON38_INCLUDE_DIR}
  # ${eigen_utils_lib_SOURCE_DIR}/include
  ${pch_INCLUDE_DIR}
  ${eigen_inc_dir}
)


add_subdirectory(GoodVibrationsWithFreeball)
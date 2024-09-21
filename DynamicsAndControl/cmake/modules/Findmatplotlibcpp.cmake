find_path(matplotlibcpp_INCLUDE_DIR
  NAMES matplotlibcpp/matplotlibcpp.h
  HINTS ${CMAKE_SOURCE_DIR}/pchpkg/external/matplotlibcpp
  PATH_SUFFIXES include
  )

# if(matplotlibcpp_FOUND)

#   set(matplotlibcpp_INCLUDE_DIRS
#     ${matplotlibcpp_INCLUDE_DIR}
#   )

# endif()

find_package(Python3 COMPONENTS Interpreter Development NumPy)
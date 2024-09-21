find_path(pch_INCLUDE_DIR
  NAMES pch/pch.h
  HINTS ${CMAKE_SOURCE_DIR}/pchpkg
  PATH_SUFFIXES include
  )

# if(pch_FOUND)

#   set(pch_INCLUDE_DIRS
#     ${pch_INCLUDE_DIR}
#   )

# endif()
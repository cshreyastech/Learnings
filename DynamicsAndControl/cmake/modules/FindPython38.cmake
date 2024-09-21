find_path(PYTHON38_INCLUDE_DIR
    NAMES Python.h
    HINTS /usr/include/python3.8/
    # PATH_SUFFIXES include
  )

find_library(PYTHON38_LIBRARY
    NAMES libpython3.8.so
    HINTS /usr/lib/x86_64-linux-gnu
    NO_DEFAULT_PATH
    REQUIRED
  )

# include(FindPackageHandleStandardArgs)
# find_package_handle_standard_args(PYTHON38 DEFAULT_MSG
#   PYTHON38_INCLUDE_DIR
#   PYTHON38_LIBRARY
# )

# if(PYTHON38_FOUND)

#   set(PYTHON38_INCLUDE_DIRS
#     ${PYTHON38_INCLUDE_DIR}
#   )

#   set(PYTHON38_LIBRARIES
#     ${PYTHON38_LIBRARY}
#   )
  
# endif()
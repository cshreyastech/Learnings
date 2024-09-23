cmake_minimum_required(VERSION 3.0.0)
project(TheFiniteElementMethodCPP)

set(HEADER_DIR
  include
)

MACRO(add_project project_name)
  # set(SRC_FILES
  #   src/${project_app}.cpp
  # )

  # ADD_EXECUTABLE(${project_app} 
  #   ${SRC_FILES}
  # )

  # target_precompile_headers(${project_app} 
  #   PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h
  # )

  # target_include_directories(${project_app}
  #   PRIVATE {HEADER_DIR}
  #   )
  
  # target_link_libraries(${project_app} 
  #   PRIVATE ${PYTHON38_LIBRARY})

  # set_target_properties(${project_app} PROPERTIES 
  #   CXX_STANDARD 20
  #   CXX_STANDARD_REQUIRED YES
  # )

  set(SRC_FILES
    src/${project_name}.cpp
  )

  set(project_app project_name_app)

  ADD_EXECUTABLE(${project_app}
    ${SRC_FILES}
  )

  target_precompile_headers(${project_app} PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h)

  target_include_directories(${project_app}
    PRIVATE ${HEADER_DIR}
  )

  target_link_libraries(${project_app} ${PYTHON38_LIBRARY})

  set_target_properties(${project_app} PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
  )
ENDMACRO()

# add_project(matplotlibtest)
add_project(03_bar_element)




##############################
# set(SRC_FILES
#   src/03_bar_element.cpp
# )

# set(project_app 03_bar_element_app)

# ADD_EXECUTABLE(${project_app}
#   ${SRC_FILES}
# )

# target_precompile_headers(${project_app} PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h)

# target_include_directories(${project_app}
#   PRIVATE ${HEADER_DIR}
# )

# target_link_libraries(${project_app} ${PYTHON38_LIBRARY})

# set_target_properties(${project_app} PROPERTIES 
#   CXX_STANDARD 20
#   CXX_STANDARD_REQUIRED YES
# )
##############################

# set(SRC_FILES
#   src/matplotlibtest.cpp
# )

# set(project_app matplotlibtest_app)

# ADD_EXECUTABLE(${project_app}
#   ${SRC_FILES}
# )

# target_precompile_headers(${project_app} PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h)

# # target_include_directories(${project_app}
# #   PRIVATE ${HEADER_DIR}
# # )

# target_link_libraries(${project_app} ${PYTHON38_LIBRARY})

# set_target_properties(${project_app} PROPERTIES 
#   CXX_STANDARD 20
#   CXX_STANDARD_REQUIRED YES
# )
cmake_minimum_required(VERSION 3.0.0)
project(TheFiniteElementMethodCPP)

set(HEADER_DIR
  include
)

MACRO(add_project project_name)
  message("project_name: " ${project_name})
  set(SRC_FILES
    src/${project_name}.cpp
  )

  set(project_app ${project_name}_app)

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
add_project(05_improved_bar_element)
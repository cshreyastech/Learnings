cmake_minimum_required(VERSION 3.0.0)

PROJECT(pigz)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -Wno-unknown-pragmas -Wcast-qual")

set(ZOPFLI
  ${CMAKE_SOURCE_DIR}/zopfli/src/zopfli
  )

#######################
set(yarn_lib yarn.o)

add_library(${yarn_lib}
  yarn.c
)

target_include_directories(${yarn_lib}
  PRIVATE ${CMAKE_SOURCE_DIR}
)

set_target_properties(${yarn_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(try_lib try.o)

add_library(${try_lib}
  try.c
)

target_include_directories(${try_lib}
  PRIVATE ${CMAKE_SOURCE_DIR}
)

set_target_properties(${try_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(deflate_lib deflate.o)

add_library(${deflate_lib}
  ${ZOPFLI}/deflate.c
)

target_include_directories(${deflate_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${deflate_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(blocksplitter_lib blocksplitter.o)

add_library(${blocksplitter_lib}
  ${ZOPFLI}/blocksplitter.c
)

target_include_directories(${blocksplitter_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${blocksplitter_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(tree_lib tree.o)

add_library(${tree_lib}
  ${ZOPFLI}/tree.c
)

target_include_directories(${tree_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${tree_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(lz77_lib lz77.o)

add_library(${lz77_lib}
  ${ZOPFLI}/lz77.c
)

target_include_directories(${lz77_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${lz77_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(cache_lib cache.o)

add_library(${cache_lib}
  ${ZOPFLI}/cache.c
)

target_include_directories(${cache_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${cache_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(hash_lib hash.o)

add_library(${hash_lib}
  ${ZOPFLI}/hash.c
)

target_include_directories(${hash_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${hash_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(util_lib util.o)

add_library(${util_lib}
  ${ZOPFLI}/util.c
)

target_include_directories(${util_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${util_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(squeeze_lib squeeze.o)

add_library(${squeeze_lib}
  ${ZOPFLI}/squeeze.c
)

target_include_directories(${squeeze_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${squeeze_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(katajainen_lib katajainen.o)

add_library(${katajainen_lib}
  ${ZOPFLI}/katajainen.c
)

target_include_directories(${katajainen_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${katajainen_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(symbols_lib symbols.o)

add_library(${symbols_lib}
  ${ZOPFLI}/symbols.c
)

target_include_directories(${symbols_lib}
  PRIVATE ${ZOPFLI}/
)

set_target_properties(${symbols_lib} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
#######################
set(ZOP
  PRIVATE ${yarn_lib}
  PRIVATE ${try_lib}
  PRIVATE ${deflate_lib}
  PRIVATE ${blocksplitter_lib}
  PRIVATE ${tree_lib}
  PRIVATE ${lz77_lib}
  PRIVATE ${cache_lib}
  PRIVATE ${hash_lib}
  PRIVATE ${util_lib}
  PRIVATE ${squeeze_lib}
  PRIVATE ${katajainen_lib}
  PRIVATE ${symbols_lib}
  PRIVATE pthread
  PRIVATE z
  PRIVATE m
  )

#######################
# set(pigz_app pigz)

# add_executable(${pigz_app}
#   pigz.c
# )

# target_include_directories(${pigz_app}
#   PRIVATE ${ZOPFLI}/
# )

# target_link_libraries(${pigz_app}
#   PRIVATE ${ZOP}
# )

# set_target_properties(${pigz_app} PROPERTIES 
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED YES
# )
# #######################
# set(unpigz_app unpigz)

# add_executable(${unpigz_app}
#   pigz.c
# )

# target_include_directories(${unpigz_app}
#   PRIVATE ${ZOPFLI}/
# )

# target_link_libraries(${unpigz_app}
#   PRIVATE ${ZOP}
# )

# set_target_properties(${unpigz_app} PROPERTIES 
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED YES
# )
# #######################
# set(pigz_array_app pigz_array)

# add_executable(${pigz_array_app}
#   pigz_array.c
# )

# target_include_directories(${pigz_array_app}
#   PRIVATE ${ZOPFLI}/
# )

# target_link_libraries(${pigz_array_app}
#   PRIVATE ${ZOP}
# )

# set_target_properties(${pigz_array_app} PROPERTIES 
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED YES
# )
#######################
set(unpigz_array_app unpigz)

add_executable(${unpigz_array_app}
  unpigz_array.c
)

target_include_directories(${unpigz_array_app}
  PRIVATE ${ZOPFLI}/
)

target_link_libraries(${unpigz_array_app}
  PRIVATE ${ZOP}
)

set_target_properties(${unpigz_array_app} PROPERTIES 
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
)
# #######################
# set(deserialize_p_vertices_app deserialize_p_vertices)

# add_executable(${deserialize_p_vertices_app}
# deserialize_p_vertices.c
# )

# set_target_properties(${deserialize_p_vertices_app} PROPERTIES 
#   CXX_STANDARD 17
#   CXX_STANDARD_REQUIRED YES
# )
#######################

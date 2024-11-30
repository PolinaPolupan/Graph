# Specify minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Add your custom algorithm library
add_library(algorithm_lib dfs.cpp)

add_definitions(-DGVDLL=1)

set(GRAPHVIZ_DIR "${CMAKE_SOURCE_DIR}/src/external/Graphviz-12.1.2-win64")

set(CGRAPH_LIB "${GRAPHVIZ_DIR}/lib/cgraph++.lib") # or .lib on Windows

find_library(CGRAPH_LIB cgraph REQUIRED)

file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.lib")

target_link_libraries(algorithm_lib graph_lib ${GVC_LIBS} ${CGRAPH_LIB})

target_include_directories(algorithm_lib PUBLIC "${GRAPHVIZ_DIR}/include/graphviz" ${CMAKE_CURRENT_SOURCE_DIR}/include)
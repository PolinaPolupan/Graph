# CMakeList.txt : CMake project for Graph, include source and define
# project specific logic here.
#
# Add source to this project's executable.
add_library(graph_lib  
graph.cpp
include/graph.h
include/hash.h
include/vertex.h 
include/initializer.h
 )

target_compile_features(graph_lib PRIVATE cxx_std_17)

# Include the header files
target_include_directories(graph_lib PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/include 
)

# Define the main executable
add_executable(graph_exe main.cpp)

target_compile_features(graph_exe PRIVATE cxx_std_17)

# Link the graph library to the main executable
target_link_libraries(graph_exe PRIVATE graph_lib algorithm_lib)

target_include_directories(graph_exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/algorithm/include
)

set(GRAPHVIZ_DIR "${CMAKE_SOURCE_DIR}/src/external/Graphviz-12.1.2-win64")

add_custom_command(TARGET graph_exe POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_directory # which executes "cmake - E copy_if_different..."
        "${GRAPHVIZ_DIR}/bin"    
        $<TARGET_FILE_DIR:graph_exe>)             


target_compile_definitions(graph_exe PRIVATE PROJECT_DIR="${CMAKE_SOURCE_DIR}")
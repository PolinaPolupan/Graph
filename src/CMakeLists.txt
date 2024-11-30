# Add the graph subdirectory
add_subdirectory(graph)
add_subdirectory(algorithm)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT graph_exe)
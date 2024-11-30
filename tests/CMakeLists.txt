# Download and install GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Create the test executable
add_executable(graph_test graph_test.cpp "initializer_test.cpp")

# Link GoogleTest and the graph library
target_link_libraries(graph_test PRIVATE gtest gtest_main graph_lib)

# Enable testing
include(GoogleTest)
gtest_discover_tests(graph_test)


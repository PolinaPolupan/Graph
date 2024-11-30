#include <gtest/gtest.h>
#include "graph.h"
#include "initializer.h"
#include <vector>

TEST(InitializerTest, CreateFromMatrixIntGraph) {
    // Example adjacency matrix
    std::vector<std::vector<bool>> matrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };

    // Expected graph structure (based on adjacency matrix)
    Graph<int> graph = Initializer<int>::createFromMatrix(matrix);

    // Verify the vertices in the graph
    std::unordered_set<int> expectedVertices = { 0, 1, 2, 3 };
    EXPECT_EQ(graph.vertices(), expectedVertices);

    // Verify the edges in the graph
    std::unordered_set<int> neighborsOf1 = { 0, 2, 3 };
    EXPECT_EQ(graph.neighbors(1), neighborsOf1);

    std::unordered_set<int> neighborsOf2 = { 1, 3 };
    EXPECT_EQ(graph.neighbors(2), neighborsOf2);

    std::unordered_set<int> neighborsOf3 = { 1, 2 };
    EXPECT_EQ(graph.neighbors(3), neighborsOf3);
}

TEST(InitializerTest, CreateFromMatrixCustomVertexGraph) {
    // Define custom vertices (StandardVertex)
    std::vector<StandardVertex<int>> customVertices = {
        StandardVertex<int>(100),
        StandardVertex<int>(200),
        StandardVertex<int>(300),
        StandardVertex<int>(400)
    };

    // Example adjacency matrix for custom vertices
    std::vector<std::vector<bool>> matrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };

    // Create a graph from the matrix
    Graph<StandardVertex<int>> graph = Initializer<StandardVertex<int>>::createFromMatrix(matrix, customVertices);

    // Verify the vertices in the graph
    std::unordered_set<StandardVertex<int>> expectedVertices = { customVertices[0], customVertices[1], customVertices[2], customVertices[3] };
    EXPECT_EQ(graph.vertices(), expectedVertices);

    // Verify the edges in the graph
    std::unordered_set<StandardVertex<int>> neighborsOf200 = { customVertices[0], customVertices[2] };
    EXPECT_EQ(graph.neighbors(customVertices[1]), neighborsOf200);

    std::unordered_set<StandardVertex<int>> neighborsOf300 = { customVertices[1], customVertices[3] };
    EXPECT_EQ(graph.neighbors(customVertices[2]), neighborsOf300);
}

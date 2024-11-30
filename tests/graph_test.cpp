#include <gtest/gtest.h>
#include "graph.h"  // Assuming the graph class is defined here

// Fixture class for setting up a graph instance before each test.
class GraphTest : public ::testing::Test {
protected:
    Graph<int> graph;

    void SetUp() override {
        // Add vertices
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addVertex(4);

        // Add edges
        graph.addEdge(1, 2);
        graph.addEdge(1, 3);
        graph.addEdge(2, 4, 3.5);
    }
};

// Test addVertex functionality
TEST_F(GraphTest, AddVertex) {
    EXPECT_EQ(graph.vertices().size(), 4); // Check if 4 vertices were added

    // Add a new vertex and check
    graph.addVertex(5);
    EXPECT_EQ(graph.vertices().size(), 5);
    EXPECT_TRUE(graph.vertices().count(5));
}

// Test addEdge and edge weights
TEST_F(GraphTest, AddEdgeAndWeight) {
    // Check if edge was added between 1 and 2, 1 and 3
    EXPECT_EQ(graph.neighbors(1).size(), 2);
    EXPECT_TRUE(graph.neighbors(1).count(2));
    EXPECT_TRUE(graph.neighbors(1).count(3));

    // Check default weight
    EXPECT_EQ(graph.edgeWeights().at({ 1, 2 }), 1.0);

    // Check weight between 2 and 4
    EXPECT_EQ(graph.edgeWeights().at({ 2, 4 }), 3.5);

    // Add an edge with a weight
    graph.addEdge(3, 4, 5.0);
    EXPECT_EQ(graph.edgeWeights().at({ 3, 4 }), 5.0);
}

// Test removeVertex
TEST_F(GraphTest, RemoveVertex) {
    // Remove vertex and check size
    EXPECT_TRUE(graph.removeVertex(2));
    EXPECT_EQ(graph.vertices().size(), 3);
    EXPECT_FALSE(graph.vertices().count(2));

    graph.printEdges();

    // Check that neighbors of vertex 1 no longer include 2
    EXPECT_FALSE(graph.neighbors(1).count(2));
}

// Test removeEdge
TEST_F(GraphTest, RemoveEdge) {
    // Remove edge and check neighbors
    EXPECT_TRUE(graph.removeEdge(1, 2));
    EXPECT_FALSE(graph.neighbors(1).count(2));
    EXPECT_FALSE(graph.neighbors(2).count(1));
}

// Test setWeight for vertex pair
TEST_F(GraphTest, SetWeightWithVertices) {
    // Set weight between two vertices
    graph.setWeight(1, 3, 10.0);
    EXPECT_EQ(graph.edgeWeights().at({ 1, 3 }), 10.0);
}

// Test setWeight for edge pair
TEST_F(GraphTest, SetWeightWithEdgePair) {
    // Create an edge pair and set its weight
    std::pair<int, int> edge = { 2, 4 };
    graph.setWeight(edge, 7.2);
    EXPECT_EQ(graph.edgeWeights().at(edge), 7.2);
}

// Test neighbors method
TEST_F(GraphTest, Neighbors) {
    // Check if neighbors are correct for vertex 1
    auto neighbors = graph.neighbors(1);
    EXPECT_EQ(neighbors.size(), 2);
    EXPECT_TRUE(neighbors.count(2));
    EXPECT_TRUE(neighbors.count(3));
}

// Test first and next iterators
TEST_F(GraphTest, Iterators) {
    // Check the first iterator for vertex 1
    auto it = graph.first(1);
    EXPECT_TRUE(*it == 2 || *it == 3);

    // Check next iterator for vertex 1
    auto next_it = graph.next(1, 1);
    EXPECT_TRUE(*next_it == 2 || *next_it == 3);
}

// Test getAdjacentByIndex method
TEST_F(GraphTest, GetAdjacentByIndex) {
    // Get adjacent vertex by index for vertex 1
    int adj_vertex = graph.getAdjacentByIndex(1, 1);

    // Since the set is unordered, it could be either 2 or 3
    EXPECT_TRUE(adj_vertex == 2 || adj_vertex == 3);
}

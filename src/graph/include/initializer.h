#pragma once

#include <graph.h>

template <typename Vertex>
class Initializer {

public:

	static Graph<int> createFromMatrix(const std::vector<std::vector<bool>>& matrix) {
		
		Graph<int> graph;

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] == 1) {
					int v1 = i;
					int v2 = j;

					graph.addVertex(v1);
					graph.addVertex(v2);
					graph.addEdge(v1, v2);
				}
			}
		}

		return graph;
	}

	static Graph<Vertex> createFromMatrix(const std::vector<std::vector<bool>>& matrix, const std::vector<Vertex>& vertices) {

		Graph<Vertex> graph;

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix.size(); j++) {
				if (matrix[i][j] == 1) {
					Vertex v1 = vertices[i];
					Vertex v2 = vertices[j];

					graph.addVertex(v1);
					graph.addVertex(v2);
				    graph.addEdge(v1, v2);
				}
			}
		}

		return graph;
	}
};
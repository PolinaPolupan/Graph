#include <iostream>
#include <graph.h>
#include <dfs.h>
#include <graph2img.h>
#include <initializer.h>
#include <vertex.h>

using namespace std;

int main() {

	vector<vector<bool>> matrix = {
		{0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 1, 0, 0, 1},
		{0, 1, 1, 0, 0},
		{0, 0, 1, 0, 0}
	};

	Graph<int> graph = Initializer<int>::createFromMatrix(matrix);

	graph.printEdges();
	graph.printEdgeWeights();
	graph.printVertices();

	printImage<int>("C:/Users/polup/Pictures/Saved Pictures/graph", "png", graph);

	graph.removeVertex(3);

	printImage<int>("C:/Users/polup/Pictures/Saved Pictures/graphRemove", "png", graph);

	graph.addVertex(6);
	graph.addEdge(2, 6);
	graph.addEdge(4, 6);

	printImage<int>("C:/Users/polup/Pictures/Saved Pictures/graphAdd", "png", graph);

	graph.setWeight({ 2, 6 }, 7);

	printImage<int>("C:/Users/polup/Pictures/Saved Pictures/graphWeight", "png", graph);

	dfs(graph);

	MarkedVertex<char, char> a('A', 'o');
	MarkedVertex<char, char> b('B', 'o');

	Graph<MarkedVertex<char, char>> graphMarked;

	graphMarked.addVertex(a);
	graphMarked.addVertex(b);
	graphMarked.addEdge(a, b);

	printImage<MarkedVertex<char, char>>("C:/Users/polup/Pictures/Saved Pictures/graphMarked", "png", graphMarked);
}
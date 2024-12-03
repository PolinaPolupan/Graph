#include <iostream>
#include <graph.h>
#include <dfs.h>
#include <graph2img.h>
#include <initializer.h>
#include <vertex.h>
#include <filesystem>
#include <windows.h>

void openImage(const std::string& filePath) {
	ShellExecute(0, "open", filePath.c_str(), 0, 0, SW_SHOWNORMAL);
}

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

	std::filesystem::path baseDir = std::filesystem::path(PROJECT_DIR);

	printImage<int>((baseDir / "output" / "graph").string(), "png", graph);

	openImage((baseDir / "output" / "graph.png").string());

	graph.removeVertex(3);

	printImage<int>((baseDir / "output" / "graphRemove").string(), "png", graph);

	openImage((baseDir / "output" / "graphRemove.png").string());

	graph.addVertex(6);
	graph.addEdge(2, 6);
	graph.addEdge(4, 6);

	printImage<int>((baseDir / "output" / "graphAdd").string(), "png", graph);

	openImage((baseDir / "output" / "graphAdd.png").string());

	graph.setWeight({ 2, 6 }, 7);

	printImage<int>((baseDir / "output" / "graphWeight").string(), "png", graph);

	openImage((baseDir / "output" / "graphWeight.png").string());

	dfs(graph);

	MarkedVertex<char, char> a('A', 'o');
	MarkedVertex<char, char> b('B', 'o');

	Graph<MarkedVertex<char, char>> graphMarked;

	graphMarked.addVertex(a);
	graphMarked.addVertex(b);
	graphMarked.addEdge(a, b);

	printImage<MarkedVertex<char, char>>((baseDir / "output" / "graphMarked").string(), "png", graphMarked);

	openImage((baseDir / "output" / "graphMarked.png").string());
}
#pragma once

#include <iostream>
#include <vector>
#include <graph.h>


template<typename Vertex>
void dfsRec(
    const Graph<Vertex>& graph, 
    std::unordered_map<Vertex, bool>& visited,
    const Vertex& s,
    std::vector<Vertex>& path
) {

    visited[s] = true;
    path.push_back(s);

    // Print the current vertex
    std::cout << "Path: \n";

    for (auto& v : path) cout << v << " ";
    cout << "\n";

    // Recursively visit all adjacent vertices
    // that are not visited yet
     for (auto& i : graph.neighbors(s))
        if (visited[i] == false)
            dfsRec(graph, visited, i, path);

     visited[s] = false;
     path.pop_back();
}


template<typename Vertex>
// Main DFS function that initializes the visited array
// and call DFSRec
void dfs(const Graph<Vertex>& graph) {
    
    std::unordered_map<Vertex, bool> visited;
    std::vector<Vertex> path;

    for (auto& v: graph.vertices())
        dfsRec(graph, visited, v, path);
}

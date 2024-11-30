#pragma once

#include <map>
#include <set>
#include <sstream>

#define GVDLL
#include <gvc.h>

#include "graph.h"


// Creates a DOT file, representing the graph, which can be used as input for visualization in Graphviz
template<typename Vertex>
void printImage(std::string fileName, const char* extension, Graph<Vertex>& graph, bool ignoreDoubleEdges = false) {

    Agraph_t* g;                            // Graphviz's special graph data structure
    std::map<Vertex, Agnode_t*> agnodes;      // A mapping between nodes of our graph to nodes in the Graphviz's graph

    // Setting up a Graphviz Context - but only once even for multiple graphs
    static GVC_t* gvc;
    if (!gvc)
        gvc = gvContext();

    g = agopen((char*)"graph", Agdirected, NULL); // Change constant to "Agdirected" for directed graphs

    for (const Vertex& node : graph.vertices()) {

        std::stringstream ss;
        ss << node;
        char label[20];
        ss >> label;
     
        agnodes[node] = agnode(g, label, true);  // 'nodeLabel' will also internally denote the node identifier in the graph

        // Setting attributes when creating the nodes
        agsafeset(agnodes[node], (char*)"color", "red", "");
    }

     std::set<std::pair<Vertex, Vertex>> alreadyAddedEdges;

     for (auto edge : graph.edgeWeights()) {

        Vertex u = edge.first.first;
        Vertex v = edge.first.second;
        int weight = edge.second;

        
        alreadyAddedEdges.insert(std::make_pair(u, v));

        std::stringstream ss;
        ss << weight;
        char edgeWeight[20];
        ss >> edgeWeight;

        Agedge_t* ghEdge = agedge(g, agnodes[u], agnodes[v], nullptr, true);

        // Setting attributes when creating the edges
        agsafeset(ghEdge, (char*)"color", "blue", "");
        agsafeset(ghEdge, (char*)"label", edgeWeight, "");
    }

     gvLayout(gvc, g, "dot");

     fileName = fileName + "." + extension;
 
     gvRenderFilename(gvc, g, extension, fileName.c_str());

     gvFreeLayout(gvc, g);

     cout << "Success: " << fileName << "\n";

     agclose(g);
}


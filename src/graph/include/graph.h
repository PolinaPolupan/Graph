#pragma once

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "hash.h"


template <typename Vertex>
class Graph {
public:
    // Add a vertex.
    void addVertex(const Vertex& vertex) {
        if (vertices_.insert(vertex).second) {
            edges_[vertex] = std::unordered_set<Vertex>();
        }
    }

    bool removeVertex(const Vertex& vertex) {
        if (vertices_.find(vertex) == vertices_.end()) { // Assert that the vertex exists
            return false;
        }

        vertices_.erase(vertex); // Remove vertex from the list

        for (auto it = edge_weights_.begin(); it != edge_weights_.end(); ) {
            
            const auto& edge = it->first;

            if (edge.first == vertex || edge.second == vertex) {
                it = edge_weights_.erase(it);  // Erase and move to the next valid iterator
            }
            else {
                ++it;  // Move to the next iterator if no deletion
            }
        }

        // Remove all edges which contain vertex
        for (auto& pair : edges_) {

            const Vertex& from = pair.first;
            std::unordered_set<Vertex>& to = pair.second;

            if (to.count(vertex)) {
                to.erase(vertex);
            }
        }

        edges_.erase(vertex);
        return true;
    }

    bool removeEdge(const Vertex& vertex1, const Vertex& vertex2) {
        if (vertices_.find(vertex1) == vertices_.end() || vertices_.find(vertex2) == vertices_.end()) {
            return false;
        }

        std::unordered_set<Vertex>& sinks = edges_[vertex1];
        
        if (sinks.find(vertex2) == sinks.end()) {
            return false;
        }

        sinks.erase(vertex2);
            
        edge_weights_.erase(std::make_pair(vertex1, vertex2));

        return true;
    }

    void addEdge(const Vertex& vertex1, const Vertex& vertex2, double weight) {

        if (vertex1 == vertex2) return; // Do not add edge of the same vertices
        
        edges_[vertex1].insert(vertex2);

        edge_weights_[std::make_pair(vertex1, vertex2)] = weight;
    }

    void addEdge(const Vertex& vertex1, const Vertex& vertex2) {
        addEdge(vertex1, vertex2, 1.0);
    }

    void setWeight(const Vertex& vertex1, const Vertex& vertex2, double weight) {
        
        edge_weights_[std::make_pair(vertex1, vertex2)] = weight;
    }

    void setWeight(const std::pair<Vertex, Vertex>& edge, double weight) {

        edge_weights_[edge] = weight;
    }

    const std::unordered_set<Vertex>& neighbors(const Vertex& vertex) const {
        return edges_.find(vertex)->second;
    }

    const std::unordered_set<Vertex>& vertices() const { return vertices_; }

    void printVertices() {

        std::cout << "Graph vertices: ";

        for (auto& vertex : vertices_) {
            std::cout << vertex << " ";
        }
        std::cout << "\n";
    }

    void printEdges() {

        std::cout << "Graph edges: \n";

        for (auto& v : edges_) {
            std::cout << "Vertex " << v.first << ": ";

            for (auto& vertex : neighbors(v.first)) {
                std::cout << vertex << " ";
           }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void printEdgeWeights() {

        std::cout << "Graph edges with weights: \n";

        for (auto& e : edge_weights_) {
            
            auto& v = e.first;
                
            std::cout << "Vertex: " << v.first << " ";
            std::cout << v.second << " ";
            std::cout << "Weight: " << e.second << " ";
       
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    const Vertex& getAdjacentByIndex(const Vertex& vertex, int index) const {
        return *next(vertex, index);
    }

    typename std::unordered_set<Vertex>::iterator first() const {
        return vertices_.begin();
    }

    typename std::unordered_set<Vertex>::iterator first(const Vertex& vertex) const {
        return edges_.at(vertex).begin();
    }

    typename std::unordered_set<Vertex>::iterator next(const Vertex& vertex, int index) const {
        return std::next(edges_.at(vertex).begin(), index);
    }

    inline const std::unordered_map<std::pair<Vertex, Vertex>, double, pair_hash>& edgeWeights() const { return edge_weights_; }

private:
    std::unordered_set<Vertex> vertices_;
    std::unordered_map<Vertex, std::unordered_set<Vertex>> edges_;
    std::unordered_map<std::pair<Vertex, Vertex>, double, pair_hash> edge_weights_;
};
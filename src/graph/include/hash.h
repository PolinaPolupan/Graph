#pragma once

#include <vertex.h>


struct pair_hash {
    template <typename T>
    std::size_t operator()(const std::pair<T, T>& p) const {
        const std::size_t h1 = std::hash<T>()(p.first);
        const std::size_t h2 = std::hash<T>()(p.second);
        // The decision below is at compile time
        return h1 ^ (h2 << 1);  // Or any other method to combine the hashes
    }
};

// Hash specialization for StandardVertex
template <typename T>
struct std::hash<StandardVertex<T>> {
    std::size_t operator()(const StandardVertex<T>& vertex) const {
        return std::hash<T>()(vertex.getData()); // Hash the data member
    }
};

// Hash specialization for MarkedVertex
template <typename T, typename K>
struct std::hash<MarkedVertex<T, K>> {
    std::size_t operator()(const MarkedVertex<T, K>& vertex) const {
        std::size_t h1 = std::hash<T>()(vertex.getData());  // Hash the data from StandardVertex
        std::size_t h2 = std::hash<K>()(vertex.getMark()); // Hash the mark

        // Combine the two hashes using XOR or any other combining method
        return h1 ^ (h2 << 1); // XOR with left shift
    }
};
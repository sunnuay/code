#include "graph.hpp"

void AdjacencyList::add(int start, int end) {
    int size = std::max(start, end) + 1;
    if (size > graph.size())
        graph.resize(size);
    graph[start].push_back(end);
}

void AdjacencyMatrix::add(int start, int end, int weight) {
    int size = std::max(start, end) + 1;
    if (size > graph.size()) {
        graph.resize(size);
        for (int i = 0; i < size; i++)
            graph[i].resize(size, -1);
    }
    graph[start][end] = weight;
}

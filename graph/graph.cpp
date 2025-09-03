#include "graph.hpp"

void Graph::add(int u, int v) {
    int size = std::max(u, v) + 1;
    if (size > graph.size())
        graph.resize(size);
    graph[u].push_back(v);
    graph[v].push_back(u);
}

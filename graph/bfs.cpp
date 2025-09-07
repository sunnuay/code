#include "graph.hpp"
#include <print>
#include <queue>

void AdjacencyList::bfs_iterative(int u) {
    visited.assign(graph.size(), false);
    std::queue<int> queue;
    visited[u] = true;
    queue.push(u);
    while (!queue.empty()) {
        u = queue.front();
        queue.pop();
        std::print("{} ", u);
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
        }
    }
    std::println();
}

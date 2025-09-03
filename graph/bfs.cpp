#include "graph.hpp"
#include <print>
#include <queue>

void Graph::bfs_iterative(int start) {
    visited.assign(graph.size(), false);
    visited[start] = true;
    std::queue<int> queue;
    queue.push(start);
    while (!queue.empty()) {
        int u = queue.front();
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

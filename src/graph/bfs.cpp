#include "graph.hpp"
#include <print>
#include <queue>
#include <vector>

void AdjacencyList::bfs_iterative(int u) {
  std::vector<bool> visited(graph.size());
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

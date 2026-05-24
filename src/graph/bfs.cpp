#include "graph.hpp"
#include <print>
#include <queue>
#include <vector>

void AdjacencyList::bfs_iterative(int start) {
  std::vector<bool> visited(graph.size());
  std::queue<int> queue;
  visited[start] = true;
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

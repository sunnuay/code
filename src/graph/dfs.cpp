#include "graph.hpp"
#include <print>
#include <stack>
#include <vector>

void AdjacencyList::dfs_iterative(int start) {
  std::vector<bool> visited(graph.size());
  std::stack<int> stack;
  visited[start] = true;
  stack.push(start);
  while (!stack.empty()) {
    int u = stack.top();
    stack.pop();
    std::print("{} ", u);
    for (int v : graph[u]) {
      if (!visited[v]) {
        visited[v] = true;
        stack.push(v);
      }
    }
  }
  std::println();
}

void AdjacencyList::dfs_recursive(int start) {
  std::vector<bool> visited(graph.size());
  auto &graph = this->graph;
  auto visit = [&](this auto self, int u) -> void {
    visited[u] = true;
    std::print("{} ", u);
    for (int v : graph[u]) {
      if (!visited[v]) {
        self(v);
      }
    }
  };
  visit(start);
  std::println();
}

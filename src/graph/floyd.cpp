#include "graph.hpp"
#include <print>
#include <vector>

void AdjacencyMatrix::floyd() {
  std::println("floyd:");
  int n = graph.size();
  std::vector<std::vector<int>> dist = graph;
  std::vector<std::vector<int>> path(n, std::vector<int>(n, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j && graph[i][j] != INF) {
        path[i][j] = j;
      }
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          path[i][j] = path[i][k];
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (path[i][j] != -1) {
        std::print("[{}] {}", dist[i][j], i);
        for (int next = path[i][j]; next != -1; next = path[next][j])
          std::print("->{}", next);
        std::println();
      }
    }
  }
}

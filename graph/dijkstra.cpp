#include "graph.hpp"
#include <print>

void AdjacencyMatrix::dijkstra(int u) {
    int n = graph.size();
    std::vector<int> dist = graph[u];
    std::vector<bool> visited(n, false);
    visited[u] = true;
    for (int i = 0; i < n - 1; i++) {
        int v = -1;
        int min_dist = INF;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                v = j;
            }
        }
        if (v == -1)
            break;
        visited[v] = true;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] > dist[v] + graph[v][j]) {
                dist[j] = dist[v] + graph[v][j];
            }
        }
    }
    std::println("{}", dist);
}

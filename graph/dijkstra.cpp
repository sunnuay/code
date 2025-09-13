#include "graph.hpp"
#include <print>

void AdjacencyMatrix::dijkstra(int start) {
    std::println("dijkstra:");
    int n = graph.size();
    std::vector<int> dist(n, INF);
    std::vector<int> path(n, -1);
    std::vector<bool> visited(n);
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0, min = INF; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1)
            break;
        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                path[v] = u;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (path[i] != -1) {
            std::print("[{}] {}", dist[i], i);
            for (int prev = path[i]; prev != -1; prev = path[prev])
                std::print("<-{}", prev);
            std::println();
        }
    }
}

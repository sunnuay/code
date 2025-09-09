#include "graph.hpp"
#include <print>

void AdjacencyMatrix::dijkstra(int u) {
    int n = graph.size();
    std::vector<int> dist(n, INF);
    std::vector<int> path(n, -1);
    std::vector<bool> visited(n);
    dist[u] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0, min = INF; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                v = j;
            }
        }
        if (v == -1)
            break;
        visited[v] = true;
        for (int j = 0; j < n; j++) {
            if (dist[j] > dist[v] + graph[v][j]) {
                dist[j] = dist[v] + graph[v][j];
                path[j] = v;
            }
        }
    }
    std::println("dijkstra:");
    for (int i = 0; i < n; i++) {
        std::print("({},{}) {}", u, i, i);
        for (int prev = path[i]; prev != -1; prev = path[prev])
            std::print("<-{}", prev);
        std::println();
    }
}

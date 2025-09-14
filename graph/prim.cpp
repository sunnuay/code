#include "graph.hpp"
#include <print>

void AdjacencyMatrix::prim(int start) {
    std::println("prim:");
    int n = graph.size();
    std::vector<int> dist(n, INF);
    std::vector<int> path(n, -1);
    std::vector<bool> visited(n);
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0, min = INF; j < n; j++) {
            if (min > dist[j] && !visited[j]) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1)
            break;
        visited[u] = true;
        for (int v = 0; v < n; v++) {
            if (dist[v] > graph[u][v] && !visited[v]) {
                dist[v] = graph[u][v];
                path[v] = u;
            }
        }
        if (path[u] != -1) {
            std::println("[{}] {}-{}", dist[u], path[u], u);
        }
    }
}

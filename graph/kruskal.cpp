#include "graph.hpp"
#include <algorithm>
#include <numeric>
#include <print>

void AdjacencyMatrix::kruskal() {
    std::println("kruskal:");
    int n = graph.size();
    std::vector<std::tuple<int, int, int>> edge;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != INF) {
                edge.emplace_back(graph[i][j], i, j);
            }
        }
    }
    std::ranges::sort(edge);
    std::vector<int> set(n);
    std::ranges::iota(set, 0);
    for (auto [w, u, v] : edge) {
        if (set[u] != set[v]) {
            std::ranges::replace(set, set[v], set[u]);
            std::println("[{}] {}-{}", w, u, v);
        }
    }
}

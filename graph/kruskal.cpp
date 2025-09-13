#include "graph.hpp"
#include <algorithm>
#include <numeric>
#include <print>

void AdjacencyMatrix::kruskal() {
    std::println("kruskal:");
    int n = graph.size();
    struct edge {
        int u, v, w;
    };
    std::vector<edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != INF) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    std::ranges::sort(edges, {}, &edge::w);
    std::vector<int> set(n);
    std::ranges::iota(set, 0);
    for (int cnt = 0, idx = 0; cnt < n - 1 && idx < edges.size(); idx++) {
        auto [u, v, w] = edges[idx];
        int set_u = set[u];
        int set_v = set[v];
        if (set_u != set_v) {
            std::println("[{}] {}-{}", w, u, v);
            cnt++;
            for (int i = 0; i < n; i++) {
                if (set[i] == set_v) {
                    set[i] = set_u;
                }
            }
        }
    }
}

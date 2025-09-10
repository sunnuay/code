#include "graph.hpp"
#include <algorithm>
#include <print>
#include <tuple>
#include <vector>

void AdjacencyMatrix::kruskal() {
    int n = graph.size();
    std::vector<std::tuple<int, int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] != INF) {
                edges.push_back({i, j, graph[i][j]});
            }
        }
    }
    std::ranges::sort(edges, {}, [](auto edge) { return std::get<2>(edge); });
    std::vector<int> set(n);
    for (int i = 0; i < n; i++)
        set[i] = i;
    int count = 0;
    int index = 0;
    std::println("kruskal:");
    while (count < n - 1 && index < edges.size()) {
        auto [u, v, w] = edges[index];
        int set_u = set[u];
        int set_v = set[v];
        if (set_u != set_v) {
            std::println("({},{},{})", u, v, w);
            count++;
            for (int i = 0; i < n; i++) {
                if (set[i] == set_v) {
                    set[i] = set_u;
                }
            }
        }
        index++;
    }
}

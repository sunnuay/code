#include "graph.hpp"

void test_bfs_dfs() {
    AdjacencyList g(6 + 1);
    g.add(0, 1), g.add(1, 0);
    g.add(0, 2), g.add(2, 0);
    g.add(0, 5), g.add(5, 0);
    g.add(1, 2), g.add(2, 1);
    g.add(1, 4), g.add(4, 1);
    g.add(2, 3), g.add(3, 2);
    g.bfs_iterative(0);
    g.dfs_iterative(0);
    g.dfs_recursive(0);
}

void test_prim_kruskal() {
    AdjacencyMatrix g(6 + 1);
    g.add(0, 1, 34), g.add(1, 0, 34);
    g.add(0, 2, 46), g.add(2, 0, 46);
    g.add(0, 5, 19), g.add(5, 0, 19);
    g.add(1, 4, 12), g.add(4, 1, 12);
    g.add(2, 3, 17), g.add(3, 2, 17);
    g.add(2, 5, 25), g.add(5, 2, 25);
    g.add(3, 4, 38), g.add(4, 3, 38);
    g.add(3, 5, 25), g.add(5, 3, 25);
    g.add(4, 5, 26), g.add(5, 4, 26);
    g.prim(0);
    g.kruskal();
}

void test_dijkstra_floyd() {
    AdjacencyMatrix g(3 + 1);
    g.add(0, 1, 4), g.add(1, 0, 6);
    g.add(0, 2, 11), g.add(2, 0, 3);
    g.add(1, 2, 2);
    g.dijkstra(0);
    g.floyd();
}

int main() {
    test_bfs_dfs();
    test_prim_kruskal();
    test_dijkstra_floyd();
}

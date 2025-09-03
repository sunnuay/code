#include "graph.hpp"

int main() {
    Graph graph;
    graph.add(0, 1);
    graph.add(0, 2);
    graph.add(1, 3);
    graph.add(1, 4);
    graph.add(2, 5);
    graph.add(2, 6);
    graph.bfs_iterative(0);
    graph.dfs_recursive(0);
    graph.dfs_iterative(0);
}

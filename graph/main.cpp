#include "graph.hpp"

int main() {
    AdjacencyMatrix am(3);
    am.add(0, 1, 4), am.add(1, 0, 6);
    am.add(0, 2, 11), am.add(2, 0, 3);
    am.add(1, 2, 2);
    am.dijkstra(0);
    am.floyd();
}

#include "graph.hpp"

int main() {
    AdjacencyMatrix am(4);
    am.add(0, 1, 4), am.add(1, 0, 6);
    am.add(0, 2, 11), am.add(2, 0, 3);
    am.add(1, 2, 2);
    am.dijkstra(0);
    am.floyd();
    am.prim(0);
    AdjacencyMatrix g(6);
    g.add(0, 1, 34), g.add(1, 0, 34);
    g.add(0, 2, 46), g.add(2, 0, 46);
    g.add(0, 5, 19), g.add(5, 0, 19);
    g.add(1, 4, 12), g.add(4, 1, 12);
    g.add(2, 3, 17), g.add(3, 2, 17);
    g.add(2, 5, 25), g.add(5, 2, 25);
    g.add(3, 4, 38), g.add(4, 3, 38);
    g.add(3, 5, 25), g.add(5, 3, 25);
    g.add(4, 5, 26), g.add(5, 4, 26);
    g.kruskal();
}

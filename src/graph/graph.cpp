#include "graph.hpp"

AdjacencyList::AdjacencyList(int n) : graph(n) {}

AdjacencyMatrix::AdjacencyMatrix(int n) : graph(n, std::vector<int>(n, INF)) {
  for (int i = 0; i < n; i++)
    graph[i][i] = 0;
}

void AdjacencyList::add(int start, int end) { graph[start].push_back(end); }

void AdjacencyMatrix::add(int start, int end, int weight) { graph[start][end] = weight; }

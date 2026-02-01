#include <vector>
#define INF 0x3fffffff

class AdjacencyList {
public:
  AdjacencyList(int n);
  void add(int start, int end);
  void bfs_iterative(int start);
  void dfs_iterative(int start);
  void dfs_recursive(int start);

private:
  std::vector<std::vector<int>> graph;
};

class AdjacencyMatrix {
public:
  AdjacencyMatrix(int n);
  void add(int start, int end, int weight);
  void prim(int start);
  void kruskal();
  void dijkstra(int start);
  void floyd();

private:
  std::vector<std::vector<int>> graph;
};

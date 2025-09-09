#include <vector>
#define INF 0x3fffffff

class AdjacencyList {
  public:
    AdjacencyList(int n);
    void add(int start, int end);
    void bfs_iterative(int u);
    void dfs_iterative(int u);
    void dfs_recursive(int u);

  private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> dfs_recursive_visited;
    void dfs_recursive_visit(int u);
};

class AdjacencyMatrix {
  public:
    AdjacencyMatrix(int n);
    void add(int start, int end, int weight);
    void prim();
    void kruskal();
    void dijkstra(int start);
    void floyd();

  private:
    std::vector<std::vector<int>> graph;
};

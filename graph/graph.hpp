#include <vector>

class AdjacencyList {
  public:
    AdjacencyList(int n);
    void add(int start, int end);
    void bfs_iterative(int u);
    void dfs_iterative(int u);
    void dfs_recursive(int u);

  private:
    int n;
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    void dfs_visit(int u);
};

class AdjacencyMatrix {
  public:
    AdjacencyMatrix(int n);
    void add(int start, int end, int weight);
    void prim();
    void kruskal();
    void dijkstra(int u);
    void floyd();

  private:
    int n;
    int INF = 0x3fffffff;
    std::vector<std::vector<int>> graph;
};

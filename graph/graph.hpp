#include <vector>

class AdjacencyList {
  public:
    void add(int start, int end);
    void bfs_iterative(int u);
    void dfs_iterative(int u);
    void dfs_recursive(int u);

  private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    void dfs_visit(int u);
};

class AdjacencyMatrix {
  public:
    void add(int start, int end, int weight);
    void prim();
    void kruskal();
    void dijkstra();
    void floyd();

  private:
    std::vector<std::vector<int>> graph;
};

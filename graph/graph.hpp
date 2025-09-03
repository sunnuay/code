#include <vector>

class Graph {
  public:
    void add(int u, int v);
    void bfs_iterative(int start);
    void dfs_iterative(int start);
    void dfs_recursive(int start);

  private:
    std::vector<std::vector<int>> graph;
    std::vector<bool> visited;
    void dfs_visit(int u);
};

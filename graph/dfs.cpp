#include "graph.hpp"
#include <print>
#include <stack>

void AdjacencyList::dfs_iterative(int u) {
    std::vector<bool> visited(graph.size());
    std::stack<int> stack;
    visited[u] = true;
    stack.push(u);
    while (!stack.empty()) {
        u = stack.top();
        stack.pop();
        std::print("{} ", u);
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                stack.push(v);
            }
        }
    }
    std::println();
}

void AdjacencyList::dfs_recursive(int u) {
    dfs_recursive_visited.assign(graph.size(), false);
    dfs_recursive_visit(u);
    std::println();
}

void AdjacencyList::dfs_recursive_visit(int u) {
    dfs_recursive_visited[u] = true;
    std::print("{} ", u);
    for (int v : graph[u])
        if (!dfs_recursive_visited[v])
            dfs_recursive_visit(v);
}

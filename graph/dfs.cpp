#include "graph.hpp"
#include <print>
#include <stack>

void Graph::dfs_iterative(int start) {
    visited.assign(graph.size(), false);
    visited[start] = true;
    std::stack<int> stack;
    stack.push(start);
    while (!stack.empty()) {
        int u = stack.top();
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

void Graph::dfs_recursive(int start) {
    visited.assign(graph.size(), false);
    dfs_visit(start);
    std::println();
}

void Graph::dfs_visit(int u) {
    visited[u] = true;
    std::print("{} ", u);
    for (int v : graph[u])
        if (!visited[v])
            dfs_visit(v);
}

#include "graph.hpp"
#include <print>
#include <stack>

void AdjacencyList::dfs_iterative(int u) {
    visited.assign(n, false);
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
    visited.assign(n, false);
    dfs_visit(u);
    std::println();
}

void AdjacencyList::dfs_visit(int u) {
    visited[u] = true;
    std::print("{} ", u);
    for (int v : graph[u])
        if (!visited[v])
            dfs_visit(v);
}

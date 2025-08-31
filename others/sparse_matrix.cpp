#include "sparse_matrix.h"
#include <print>

SparseMatrix::SparseMatrix() {
}

SparseMatrix::SparseMatrix(std::initializer_list<Node> list) : node(list) {
}

SparseMatrix SparseMatrix::transpose() {
    SparseMatrix sm;
    sm.node.resize(node.size());
    int cols = 0;
    for (auto [row, col, val] : node)
        cols = std::max(cols, col + 1);
    std::vector<int> number(cols);
    std::vector<int> position(cols);
    for (auto [row, col, val] : node)
        number[col]++;
    for (int i = 1; i < cols; ++i)
        position[i] = position[i - 1] + number[i - 1];
    for (auto [row, col, val] : node)
        sm.node[position[col]++] = {col, row, val};
    return sm;
}

void SparseMatrix::print() {
    std::println("SparseMatrix:");
    for (auto [row, col, val] : node)
        std::println("{} {} {}", row, col, val);
}

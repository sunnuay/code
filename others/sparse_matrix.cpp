#include "sparse_matrix.hpp"
#include <print>

SparseMatrix SparseMatrix::transpose() {
    SparseMatrix sm;
    sm.data.resize(data.size());
    int cols = 0;
    for (auto [row, col, val] : data)
        cols = std::max(cols, col + 1);
    std::vector<int> number(cols);
    std::vector<int> position(cols);
    for (auto [row, col, val] : data)
        number[col]++;
    for (int i = 1; i < cols; ++i)
        position[i] = position[i - 1] + number[i - 1];
    for (auto [row, col, val] : data)
        sm.data[position[col]++] = {col, row, val};
    return sm;
}

void SparseMatrix::print() {
    std::println("SparseMatrix:");
    for (auto [row, col, val] : data)
        std::println("{} {} {}", row, col, val);
}

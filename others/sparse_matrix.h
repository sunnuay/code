#include <vector>

struct SparseMatrix {
    struct Node {
        int row, col, val;
    };
    std::vector<Node> node;
    SparseMatrix();
    SparseMatrix(std::initializer_list<Node> list);
    SparseMatrix transpose();
    void print();
};

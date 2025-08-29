struct SparseMatrixNode {
    int row, col, val;
};

struct SparseMatrix {
    SparseMatrix();
    SparseMatrix transpose();
    void print();
    void sort();
    SparseMatrixNode *node;
    int size;
};

#include "deque.h"
#include "sparse_matrix.h"
#include "string_matching.h"

void test_deque() {
    Deque deque;
    deque.push_front(1);
    deque.push_back(2);
    deque.pop_front();
    deque.pop_back();
}

void test_sparse_matrix() {
    SparseMatrix sm = {{3, 2, 1}, {1, 2, 3}, {1, 1, 4}, {5, 1, 4}};
    sm.print();
    sm.transpose().print();
    sm.transpose().transpose().print();
}

void test_string_matching() {
    StringMaching sm;
    sm.text = "ABABABC";
    sm.pattern = "ABABC";
    sm.print();
}

int main() {
    test_deque();
    test_sparse_matrix();
    test_string_matching();
}

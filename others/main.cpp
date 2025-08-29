#include "deque.h"

void test_deque() {
    Deque deque;
    deque.push_front(1);
    deque.push_back(2);
    deque.pop_front();
    deque.pop_back();
}

void test_sparse_matrix() {
}

int main() {
    test_deque();
    test_sparse_matrix();
}

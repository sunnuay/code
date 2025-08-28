#include "others.h"

void test_deque() {
    Deque deque;
    deque.push_front(1);
    deque.push_back(2);
    deque.pop_front();
    deque.pop_back();
}

int main() {
    test_deque();
}

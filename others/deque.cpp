#include "deque.h"
#include <print>

Deque::Deque() {
    head = tail = 0;
}

int Deque::size() {
    return (tail - head + MAX) % MAX;
}

bool Deque::push_front(int val) {
    if (size() == MAX - 1)
        return false;
    data[head] = val;
    head = (head - 1 + MAX) % MAX;
    return true;
}

bool Deque::push_back(int val) {
    if (size() == MAX - 1)
        return false;
    tail = (tail + 1) % MAX;
    data[tail] = val;
    return true;
}

bool Deque::pop_front() {
    if (size() == 0)
        return false;
    head = (head + 1) % MAX;
    std::println("{}", data[head]);
    return true;
}

bool Deque::pop_back() {
    if (size() == 0)
        return false;
    std::println("{}", data[tail]);
    tail = (tail - 1 + MAX) % MAX;
    return true;
}

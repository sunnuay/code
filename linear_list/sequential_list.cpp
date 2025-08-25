#include "linear_list.h"
#include <print>

SequentialList::SequentialList() {
    size = 0;
}

int SequentialList::find(int val) {
    for (int i = 0; i < size; ++i)
        if (data[i] == val)
            return i;

    return -1;
}

bool SequentialList::insert(int val, int idx) {
    if (size >= MAX_SIZE || idx < 0 || idx > size)
        return false;

    for (int i = size; i > idx; --i)
        data[i] = data[i - 1];

    data[idx] = val;
    size++;
    return true;
}

bool SequentialList::insert(int val) {
    return insert(val, size);
}

bool SequentialList::erase(int idx) {
    if (idx < 0 || idx >= size)
        return false;

    for (int i = idx; i < size - 1; ++i)
        data[i] = data[i + 1];

    size--;
    return true;
}

bool SequentialList::erase() {
    return erase(size - 1);
}

void SequentialList::print() {
    for (int i = 0; i < size; ++i)
        std::print("{} ", data[i]);
    std::println();
}

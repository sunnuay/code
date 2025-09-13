#include "list.hpp"
#include <print>

StaticLinkedList::StaticLinkedList() {
    p[0].next = -1;
    for (int i = 1; i < MAX - 1; i++)
        p[i].next = i + 1;
    p[MAX - 1].next = -1;
    head = tail = size = 0;
    free = 1;
}

void StaticLinkedList::print() {
    int temp = p[head].next;
    while (temp != -1) {
        std::print("{} ", p[temp].data);
        temp = p[temp].next;
    }
    std::println();
}

bool StaticLinkedList::insert(int val, int idx) {
    if (free == -1 || idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    int temp = head;
    for (int i = 0; i < idx; i++)
        temp = p[temp].next;
    int node = free;
    free = p[free].next;
    p[node].data = val;
    p[node].next = p[temp].next;
    p[temp].next = node;
    size++;
    return true;
}

bool StaticLinkedList::insert(int val) {
    if (free == -1)
        return false;
    int node = free;
    free = p[free].next;
    p[node].data = val;
    p[node].next = p[tail].next;
    p[tail].next = node;
    tail = node;
    size++;
    return true;
}

bool StaticLinkedList::remove(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    int temp = head;
    for (int i = 0; i < idx; i++)
        temp = p[temp].next;
    int node = p[temp].next;
    p[temp].next = p[node].next;
    if (tail == node)
        tail = temp;
    p[node].next = free;
    free = node;
    size--;
    return true;
}

bool StaticLinkedList::remove() {
    return remove(size - 1);
}

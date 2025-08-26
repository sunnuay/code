#include "linear_list.h"
#include <print>

StaticLinkedList::StaticLinkedList() {
    n[0].next = -1;
    for (int i = 1; i < MAX_SIZE - 1; i++)
        n[i].next = i + 1;
    n[MAX_SIZE - 1].next = -1;
    head = tail = size = 0;
    free = 1;
}

int StaticLinkedList::find(int val) {
    int temp = n[head].next;
    for (int i = 0; i < size; i++) {
        if (n[temp].data == val)
            return i;
        temp = n[temp].next;
    }
    return -1;
}

bool StaticLinkedList::insert(int val, int idx) {
    if (free == -1 || idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    int temp = head;
    for (int i = 0; i < idx; i++)
        temp = n[temp].next;
    int node = free;
    free = n[free].next;
    n[node].data = val;
    n[node].next = n[temp].next;
    n[temp].next = node;
    size++;
    return true;
}

bool StaticLinkedList::insert(int val) {
    if (free == -1)
        return false;
    int node = free;
    free = n[free].next;
    n[node].data = val;
    n[node].next = n[tail].next;
    n[tail].next = node;
    tail = node;
    size++;
    return true;
}

bool StaticLinkedList::erase(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    int temp = head;
    for (int i = 0; i < idx; i++)
        temp = n[temp].next;
    int node = n[temp].next;
    n[temp].next = n[node].next;
    if (tail == node)
        tail = temp;
    n[node].next = free;
    free = node;
    size--;
    return true;
}

bool StaticLinkedList::erase() {
    return erase(size - 1);
}

void StaticLinkedList::print() {
    int temp = n[head].next;
    while (temp != -1) {
        std::print("{} ", n[temp].data);
        temp = n[temp].next;
    }
    std::println();
}

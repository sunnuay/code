#include "linear_list.h"
#include <print>

SinglyLinkedList::SinglyLinkedList() {
    head = new Node;
    head->next = nullptr;
    tail = head;
    size = 0;
}

int SinglyLinkedList::find(int val) {
    Node *temp = head->next;
    for (int i = 0; i < size; i++) {
        if (temp->data == val)
            return i;
        temp = temp->next;
    }
    return -1;
}

bool SinglyLinkedList::insert(int val, int idx) {
    if (idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    Node *prev = head;
    for (int i = 0; i < idx; i++)
        prev = prev->next;
    Node *node = new Node;
    node->data = val;
    node->next = prev->next;
    prev->next = node;
    size++;
    return true;
}

bool SinglyLinkedList::insert(int val) {
    Node *node = new Node;
    node->data = val;
    node->next = tail->next;
    tail->next = node;
    tail = node;
    size++;
    return true;
}

bool SinglyLinkedList::erase(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    Node *prev = head;
    for (int i = 0; i < idx; i++)
        prev = prev->next;
    Node *node = prev->next;
    prev->next = node->next;
    if (tail == node)
        tail = prev;
    delete node;
    size--;
    return true;
}

bool SinglyLinkedList::erase() {
    return erase(size - 1);
}

void SinglyLinkedList::print() {
    Node *temp = head->next;
    while (temp) {
        std::print("{} ", temp->data);
        temp = temp->next;
    }
    std::println();
}

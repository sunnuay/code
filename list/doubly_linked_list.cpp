#include "list.hpp"
#include <print>

DoublyLinkedList::DoublyLinkedList() {
    head = new Node;
    head->prev = nullptr;
    head->next = nullptr;
    tail = head;
    size = 0;
}

void DoublyLinkedList::print() {
    Node *temp = head->next;
    while (temp) {
        std::print("{} ", temp->data);
        temp = temp->next;
    }
    std::println();
}

bool DoublyLinkedList::insert(int val, int idx) {
    if (idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    Node *temp = head;
    for (int i = 0; i < idx; i++)
        temp = temp->next;
    Node *node = new Node;
    node->data = val;
    node->next = temp->next;
    node->prev = temp;
    temp->next->prev = node;
    temp->next = node;
    size++;
    return true;
}

bool DoublyLinkedList::insert(int val) {
    Node *node = new Node;
    node->data = val;
    node->prev = tail;
    node->next = tail->next;
    tail->next = node;
    tail = node;
    size++;
    return true;
}

bool DoublyLinkedList::remove(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    if (idx == size - 1)
        return remove();
    Node *temp = head;
    for (int i = 0; i < idx; i++)
        temp = temp->next;
    Node *node = temp->next;
    temp->next = node->next;
    node->next->prev = temp;
    delete node;
    size--;
    return true;
}

bool DoublyLinkedList::remove() {
    if (size == 0)
        return false;
    Node *node = tail;
    tail = tail->prev;
    tail->next = node->next;
    delete node;
    size--;
    return true;
}

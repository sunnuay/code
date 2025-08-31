#include "list.hpp"
#include <print>

SinglyLinkedList::SinglyLinkedList() {
    head = new Node;
    head->next = nullptr;
    tail = head;
    size = 0;
}

void SinglyLinkedList::print() {
    Node *temp = head->next;
    while (temp) {
        std::print("{} ", temp->data);
        temp = temp->next;
    }
    std::println();
}

bool SinglyLinkedList::insert(int val, int idx) {
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
    temp->next = node;
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
    Node *temp = head;
    for (int i = 0; i < idx; i++)
        temp = temp->next;
    Node *node = temp->next;
    temp->next = node->next;
    if (tail == node)
        tail = temp;
    delete node;
    size--;
    return true;
}

bool SinglyLinkedList::erase() {
    return erase(size - 1);
}

#include "list.hpp"
#include <print>

CircularLinkedList::CircularLinkedList() {
    tail = new Node;
    tail->next = tail;
    size = 0;
}

void CircularLinkedList::print() {
    Node *head = tail->next;
    Node *temp = head->next;
    while (temp != head) {
        std::print("{} ", temp->data);
        temp = temp->next;
    }
    std::println();
}

bool CircularLinkedList::insert(int val, int idx) {
    if (idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    Node *temp = tail->next;
    for (int i = 0; i < idx; i++)
        temp = temp->next;
    Node *node = new Node;
    node->data = val;
    node->next = temp->next;
    temp->next = node;
    size++;
    return true;
}

bool CircularLinkedList::insert(int val) {
    Node *node = new Node;
    node->data = val;
    node->next = tail->next;
    tail->next = node;
    tail = node;
    size++;
    return true;
}

bool CircularLinkedList::remove(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    Node *temp = tail->next;
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

bool CircularLinkedList::remove() {
    return remove(size - 1);
}

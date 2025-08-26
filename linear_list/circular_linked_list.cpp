#include "linear_list.h"
#include <print>

CircularLinkedList::CircularLinkedList() {
    tail = new Node;
    tail->next = tail;
    size = 0;
}

int CircularLinkedList::find(int val) {
    Node *head = tail->next;
    Node *temp = head->next;
    for (int i = 0; i < size; i++) {
        if (temp->data == val)
            return i;
        temp = temp->next;
    }
    return -1;
}

bool CircularLinkedList::insert(int val, int idx) {
    if (idx < 0 || idx > size)
        return false;
    if (idx == size)
        return insert(val);
    Node *prev = tail->next;
    for (int i = 0; i < idx; i++)
        prev = prev->next;
    Node *node = new Node;
    node->data = val;
    node->next = prev->next;
    prev->next = node;
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

bool CircularLinkedList::erase(int idx) {
    if (idx < 0 || idx >= size)
        return false;
    Node *prev = tail->next;
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

bool CircularLinkedList::erase() {
    return erase(size - 1);
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

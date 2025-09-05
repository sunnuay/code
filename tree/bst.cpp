#include "tree.hpp"
#include <print>

void BST::print() {
    print(root);
    std::println();
}

void BST::print(Node *node) {
    if (node == nullptr)
        return;
    print(node->l);
    std::print("{} ", node->data);
    print(node->r);
}

bool BST::insert(int data) {
    return insert(root, data);
}

bool BST::insert(Node *&node, int data) {
    if (node == nullptr) {
        node = new Node{data, nullptr, nullptr};
        return true;
    } else if (data < node->data) {
        return insert(node->l, data);
    } else if (data > node->data) {
        return insert(node->r, data);
    } else {
        return false;
    }
}

bool BST::remove(int data) {
    return remove(root, data);
}

bool BST::remove(Node *&node, int data) {
    if (node == nullptr) {
        return false;
    } else if (data < node->data) {
        return remove(node->l, data);
    } else if (data > node->data) {
        return remove(node->r, data);
    } else {
        erase(node);
        return true;
    }
}

void BST::erase(Node *&node) {
    Node *pred, *temp;
    if (node->l == nullptr) {
        temp = node;
        node = node->r;
        delete temp;
    } else if (node->r == nullptr) {
        temp = node;
        node = node->l;
        delete temp;
    } else {
        pred = node;
        temp = node->l;
        while (temp->r != nullptr)
            pred = temp, temp = temp->r;
        node->data = temp->data;
        if (pred == node)
            pred->l = temp->l;
        else
            pred->r = temp->l;
        delete temp;
    }
}

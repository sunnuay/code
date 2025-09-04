#include "tree.hpp"
#include <print>

void BST::print() {
    print(root);
    std::println();
}

void BST::print(Node *node) {
    if (node) {
        print(node->l);
        std::print("{} ", node->data);
        print(node->r);
    }
}

bool BST::insert(int data) {
    Node *&curr = root;
    while (curr) {
        if (data < curr->data) {
            curr = curr->l;
        } else if (data > curr->data) {
            curr = curr->r;
        } else {
            return false;
        }
    }
    curr = new Node{data, nullptr, nullptr};
    return true;
}

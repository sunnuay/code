#include "tree.hpp"
#include <print>

BST::BST() : root(nullptr) {
}

bool BST::search(int data) {
    return search(root, data) != nullptr;
}

void BST::insert(int data) {
    root = insert(root, data);
}

void BST::remove(int data) {
    root = remove(root, data);
}

void BST::print() {
    print(root);
    std::println();
}

BST::Node *BST::search(Node *node, int data) {
    if (node == nullptr || node->data == data)
        return node;
    if (data < node->data)
        return search(node->left, data);
    else
        return search(node->right, data);
}

BST::Node *BST::insert(Node *node, int data) {
    if (node == nullptr)
        return new Node{data, nullptr, nullptr};
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

BST::Node *BST::remove(Node *node, int data) {
    if (node == nullptr)
        return nullptr;
    if (data < node->data)
        node->left = remove(node->left, data);
    else if (data > node->data)
        node->right = remove(node->right, data);
    else {
        if (node->left == nullptr) {
            Node *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node *temp = node->left;
            delete node;
            return temp;
        }
        Node *successor = node->right;
        while (successor->left != nullptr)
            successor = successor->left;
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
    }
    return node;
}

void BST::print(Node *node) {
    if (node) {
        print(node->left);
        std::print("{} ", node->data);
        print(node->right);
    }
}

#include "tree.hpp"
#include <print>
#include <queue>
#include <stack>

void BST::inorder() {
    if (!root)
        return;
    std::stack<Node *> s;
    Node *current = root;
    while (current || !s.empty()) {
        while (current) {
            s.push(current);
            current = current->l;
        }
        current = s.top();
        s.pop();
        std::print("{} ", current->data);
        current = current->r;
    }
    std::println();
}

void BST::preorder() {
    if (!root)
        return;
    std::stack<Node *> s;
    s.push(root);
    while (!s.empty()) {
        Node *current = s.top();
        s.pop();
        std::print("{} ", current->data);
        if (current->r)
            s.push(current->r);
        if (current->l)
            s.push(current->l);
    }
    std::println();
}

void BST::postorder() {
    if (!root)
        return;
    std::stack<Node *> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node *current = s1.top();
        s1.pop();
        s2.push(current);
        if (current->l)
            s1.push(current->l);
        if (current->r)
            s1.push(current->r);
    }
    while (!s2.empty()) {
        std::print("{} ", s2.top()->data);
        s2.pop();
    }
    std::println();
}

void BST::levelorder() {
    if (!root)
        return;
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node *current = q.front();
        q.pop();
        std::print("{} ", current->data);
        if (current->l)
            q.push(current->l);
        if (current->r)
            q.push(current->r);
    }
    std::println();
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
        remove(node);
        return true;
    }
}

void BST::remove(Node *&node) {
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

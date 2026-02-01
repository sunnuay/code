#include "tree.hpp"
#include <print>
#include <queue>
#include <ranges>
#include <stack>
#include <vector>

void BST::inorder() {
  if (root == nullptr)
    return;
  std::vector<int> data;
  std::stack<Node *> stack;
  Node *node = root;
  while (node || !stack.empty()) {
    if (node) {
      stack.push(node);
      node = node->l;
    } else {
      node = stack.top();
      stack.pop();
      data.push_back(node->data);
      node = node->r;
    }
  }
  std::println("{}", data);
}

void BST::preorder() {
  if (root == nullptr)
    return;
  std::vector<int> data;
  std::stack<Node *> stack;
  Node *node = root;
  while (node || !stack.empty()) {
    if (node) {
      data.push_back(node->data);
      stack.push(node);
      node = node->l;
    } else {
      node = stack.top();
      stack.pop();
      node = node->r;
    }
  }
  std::println("{}", data);
}

void BST::postorder() {
  if (root == nullptr)
    return;
  std::vector<int> data;
  std::stack<Node *> stack;
  Node *node = root;
  while (node || !stack.empty()) {
    if (node) {
      data.push_back(node->data);
      stack.push(node);
      node = node->r;
    } else {
      node = stack.top();
      stack.pop();
      node = node->l;
    }
  }
  std::println("{}", data | std::views::reverse);
}

void BST::levelorder() {
  if (root == nullptr)
    return;
  std::vector<int> data;
  std::queue<Node *> queue;
  queue.push(root);
  while (!queue.empty()) {
    Node *node = queue.front();
    queue.pop();
    data.push_back(node->data);
    if (node->l)
      queue.push(node->l);
    if (node->r)
      queue.push(node->r);
  }
  std::println("{}", data);
}

bool BST::insert(int data) { return insert(root, data); }

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

bool BST::remove(int data) { return remove(root, data); }

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

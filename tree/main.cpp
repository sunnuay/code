#include "tree.hpp"

int main() {
    BST tree;
    tree.insert(1);
    tree.remove(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(1);
    tree.remove(4);
    tree.print();
}

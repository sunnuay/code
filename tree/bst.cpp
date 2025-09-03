#include "tree.hpp"

int main() {
    BST tree;
    tree.insert(0);
    tree.insert(7);
    tree.insert(2);
    tree.insert(1);
    if (tree.search(0))
        tree.remove(0);
    tree.print();
}

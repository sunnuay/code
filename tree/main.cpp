#include "tree.hpp"

void test_bst() {
    BST tree;
    tree.insert(1);
    tree.remove(1);
    tree.insert(4);
    tree.insert(5);
    tree.insert(1);
    tree.remove(4);
    tree.print();
}

void test_huffman() {
    std::string text = "AAAAAAAAABBBBBBZZCCC";
    std::map<char, int> count;
    for (char c : text)
        count[c]++;
    Huffman huffman(count);
    if (text == huffman.decode(huffman.encode(text)))
        huffman.print();
}

int main() {
    test_bst();
    test_huffman();
}

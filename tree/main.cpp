#include "tree.hpp"
#include <print>

void test_BST() {
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
    std::string text = "this is an example for huffman encoding";
    std::map<char, int> count;
    for (char c : text)
        count[c]++;
    Huffman huffman(count);
    std::string encoded = huffman.encode("example");
    std::string decoded = huffman.decode(encoded);
    std::println("{}", encoded);
    std::println("{}", decoded);
}

int main() {
    test_BST();
    test_huffman();
}

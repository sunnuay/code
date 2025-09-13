#include "tree.hpp"

void test_bst() {
    BST bst;
    bst.insert(1), bst.insert(4), bst.insert(7);
    bst.insert(2), bst.insert(5), bst.insert(8);
    bst.insert(3), bst.insert(6), bst.insert(9);
    bst.remove(1);
    bst.remove(4);
    bst.inorder();
    bst.preorder();
    bst.postorder();
    bst.levelorder();
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

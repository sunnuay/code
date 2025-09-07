#include "tree.hpp"
#include <print>

Huffman::Huffman(std::map<char, int> count) {
    num = count.size();
    if (num < 2)
        throw;
    tree = new Node[2 * num - 1];
    table = new Code[num];
    int i = 0;
    for (auto [key, val] : count) {
        table[i].data = key;
        tree[i].weight = val;
        tree[i].parent = tree[i].lchild = tree[i].rchild = -1;
        i++;
    }
    for (i = num; i < 2 * num - 1; i++) {
        int x = -1;
        for (int j = 0, min = INT_MAX; j < i; j++)
            if (tree[j].parent == -1 && tree[j].weight < min)
                min = tree[j].weight, x = j;
        int y = -1;
        for (int j = 0, min = INT_MAX; j < i; j++)
            if (tree[j].parent == -1 && tree[j].weight < min && j != x)
                min = tree[j].weight, y = j;
        tree[x].parent = tree[y].parent = i;
        tree[i].parent = -1;
        tree[i].lchild = x;
        tree[i].rchild = y;
        tree[i].weight = tree[x].weight + tree[y].weight;
    }
    build_table(2 * num - 2, "");
}

void Huffman::build_table(int i, std::string code) {
    if (i < num) {
        table[i].code = code;
        return;
    }
    build_table(tree[i].lchild, code + "0");
    build_table(tree[i].rchild, code + "1");
}

std::string Huffman::encode(std::string text) {
    std::string encoded = "";
    for (char c : text) {
        for (int i = 0; i < num; i++) {
            if (table[i].data == c) {
                encoded += table[i].code;
                break;
            }
        }
    }
    return encoded;
}

std::string Huffman::decode(std::string text) {
    std::string decoded = "";
    int curr = 2 * num - 2;
    for (char bit : text) {
        if (bit == '0')
            curr = tree[curr].lchild;
        else
            curr = tree[curr].rchild;
        if (curr < num) {
            decoded += table[curr].data;
            curr = 2 * num - 2;
        }
    }
    return decoded;
}

void Huffman::print() {
    std::println("index | parent lchild rchild weight | data code");
    std::println("------+-----------------------------+----------");
    for (int i = 0; i < 2 * num - 1; i++) {
        if (i < num)
            std::println("{:>5} | {:>6} {:>6} {:>6} {:>6} | {:^4} {}",
                         i,
                         tree[i].parent,
                         tree[i].lchild,
                         tree[i].rchild,
                         tree[i].weight,
                         table[i].data,
                         table[i].code);
        else
            std::println("{:>5} | {:>6} {:>6} {:>6} {:>6} |",
                         i,
                         tree[i].parent,
                         tree[i].lchild,
                         tree[i].rchild,
                         tree[i].weight);
    }
}

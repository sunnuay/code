#include <map>
#include <string>

class BST {
public:
  void inorder();
  void preorder();
  void postorder();
  void levelorder();
  bool insert(int data);
  bool remove(int data);

private:
  struct Node {
    int data;
    Node *l;
    Node *r;
  };
  Node *root = nullptr;
  bool insert(Node *&node, int data);
  bool remove(Node *&node, int data);
  void remove(Node *&node);
};

class Huffman {
public:
  Huffman(std::map<char, int> count);
  std::string encode(std::string text);
  std::string decode(std::string text);
  void print();

private:
  struct Node {
    int parent;
    int lchild;
    int rchild;
    int weight;
  };
  struct Code {
    char data;
    std::string code;
  };
  int num;
  Node *tree;
  Code *table;
  void build_table(int i, std::string code);
};

class BST {
  public:
    void print();
    bool insert(int data);
    bool remove(int data);

  private:
    struct Node {
        int data;
        Node *l;
        Node *r;
    };
    Node *root = nullptr;
    void print(Node *node);
};

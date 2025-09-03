class BST {
  public:
    BST();
    bool search(int data);
    void insert(int data);
    void remove(int data);
    void print();

  private:
    struct Node {
        int data;
        Node *left;
        Node *right;
    };
    Node *root;
    Node *search(Node *node, int data);
    Node *insert(Node *node, int data);
    Node *remove(Node *node, int data);
    void print(Node *node);
};

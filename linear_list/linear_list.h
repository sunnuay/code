#define MAX_SIZE 100

class SequentialList {
  public:
    SequentialList();
    int find(int val);
    bool insert(int val, int idx);
    bool insert(int val);
    bool erase(int idx);
    bool erase();
    void print();

  private:
    int data[MAX_SIZE];
    int size;
};

class SinglyLinkedList {
  public:
    SinglyLinkedList();
    int find(int val);
    bool insert(int val, int idx);
    bool insert(int val);
    bool erase(int idx);
    bool erase();
    void print();

  private:
    struct Node {
        int data;
        Node *next;
    };
    Node *head;
    Node *tail;
    int size;
};

class CircularLinkedList {
  public:
    CircularLinkedList();

  private:
    struct Node {
        int data;
        Node *next;
    };
    Node *tail;
    int size;
};

class DoublyLinkedList {
  public:
    DoublyLinkedList();

  private:
    struct Node {
        int data;
        Node *prev;
        Node *next;
    };
    Node *head;
    Node *tail;
    int size;
};

class StaticLinkedList {
  public:
    StaticLinkedList();

  private:
    struct Node {
        int data;
        int next;
    };
    Node node[MAX_SIZE];
    int head;
    int tail;
    int size;
    int free;
};

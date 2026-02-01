#define MAX 100

class SequentialList {
public:
  SequentialList();
  void print();
  bool insert(int val, int idx);
  bool insert(int val);
  bool remove(int idx);
  bool remove();

private:
  int data[MAX];
  int size;
};

class SinglyLinkedList {
public:
  SinglyLinkedList();
  void print();
  bool insert(int val, int idx);
  bool insert(int val);
  bool remove(int idx);
  bool remove();

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
  void print();
  bool insert(int val, int idx);
  bool insert(int val);
  bool remove(int idx);
  bool remove();

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
  void print();
  bool insert(int val, int idx);
  bool insert(int val);
  bool remove(int idx);
  bool remove();

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
  void print();
  bool insert(int val, int idx);
  bool insert(int val);
  bool remove(int idx);
  bool remove();

private:
  struct Node {
    int data;
    int next;
  };
  Node p[MAX];
  int head;
  int tail;
  int free;
  int size;
};

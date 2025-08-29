#define MAX 100

class Deque {
  public:
    Deque();
    int size();
    bool push_front(int val);
    bool push_back(int val);
    bool pop_front();
    bool pop_back();

  private:
    int data[MAX];
    int head;
    int tail;
};

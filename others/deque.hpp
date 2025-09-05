#define MAX 100

class Deque {
  public:
    bool push_front(int val);
    bool push_back(int val);
    bool pop_front();
    bool pop_back();

  private:
    int data[MAX];
    int head = 0;
    int tail = 0;
    int size();
};

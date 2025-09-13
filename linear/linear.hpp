#include <string>
#include <tuple>
#include <vector>
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

struct SparseMatrix {
    std::vector<std::tuple<int, int, int>> data;
    SparseMatrix transpose();
    void print();
};

struct StringMatching {
    std::string txt, pat;
    void bf();
    void kmp();
    std::vector<int> pf();
};

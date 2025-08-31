#include <vector>
#include <tuple>

struct SparseMatrix {
    std::vector<std::tuple<int, int, int>> data;
    SparseMatrix transpose();
    void print();
};

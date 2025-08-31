#include <tuple>
#include <vector>

struct SparseMatrix {
    std::vector<std::tuple<int, int, int>> data;
    SparseMatrix transpose();
    void print();
};

#include <string>
#include <vector>

struct StringMatching {
    std::string txt, pat;
    void print();
    int bf();
    int kmp();
    std::vector<int> pf();
};

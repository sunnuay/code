#include <string>

struct StringMaching {
    std::string text, pattern;
    int brute_force();
    int prefix_function();
    int knuth_morris_pratt();
    void print();
};

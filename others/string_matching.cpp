#include "string_matching.hpp"
#include <print>
#include <vector>

int StringMaching::bf() {
    int i = 0, j = 0;
    while (i < txt.size() && j < pat.size())
        if (txt[i] == pat[j])
            i++, j++;
        else
            i = i - j + 1, j = 0;
    return j == pat.size() ? i - j : -1;
}

int StringMaching::kmp() {
    std::vector<int> next(pat.size());
    // next
    int i = 0, j = 0;
    while (i < txt.size() && j < pat.size())
        if (txt[i] == pat[j])
            i++, j++;
        else if (next[j])
            j = next[j];
        else
            i++, j = 0;
    return j == pat.size() ? i - j : -1;
}

void StringMaching::print() {
    std::println("BF: {}", bf());
    std::println("KMP: {}", kmp());
}

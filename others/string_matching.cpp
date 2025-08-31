#include "string_matching.h"
#include <print>
#include <vector>

int StringMaching::kmp() {
    if (pattern.empty())
        return 0;
    if (text.size() < pattern.size())
        return -1;
    std::string str = pattern + "#" + text;
    std::vector<int> pi(str.size());
    for (int i = 1; i < str.size(); i++) {
        int len = pi[i - 1];
        while (len > 0 && str[i] != str[len])
            len = pi[len - 1];
        if (str[i] == str[len])
            len++;
        pi[i] = len;
        if (pi[i] == pattern.size())
            return i - 2 * pattern.size();
    }
    return -1;
}

void StringMaching::print() {
    std::println("KMP: {}", kmp());
}

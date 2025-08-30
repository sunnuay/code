#include "string_matching.h"

std::vector<int> lps(const std::string &pattern) {
    int n = pattern.length();
    std::vector<int> next(n, 0);

    // length 表示当前最长公共前后缀的长度
    for (int i = 1, length = 0; i < n;) {
        if (pattern[i] == pattern[length]) {
            // 如果匹配，长度加一
            length++;
            next[i] = length;
            i++;
        } else {
            if (length != 0) {
                // 如果不匹配，回溯到上一个可能匹配的位置
                length = next[length - 1];
            } else {
                // 如果 length 已经是 0，表示没有公共前后缀
                next[i] = 0;
                i++;
            }
        }
    }
    return next;
}

int kmp(const std::string &text, const std::string &pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0)
        return 0; // 空模式串匹配任何字符串的开头
    if (n < m)
        return -1; // 主串比模式串短，不可能匹配

    std::vector<int> next = lps(pattern);

    // i 是主串指针，j 是模式串指针
    for (int i = 0, j = 0; i < n;) {
        if (text[i] == pattern[j]) {
            // 如果字符匹配，两个指针都后移
            i++;
            j++;
        }

        if (j == m) {
            // 模式串完全匹配
            return i - j; // 返回匹配的起始位置
        } else if (i < n && text[i] != pattern[j]) {
            // 如果不匹配
            if (j != 0) {
                // 利用 next 数组移动模式串指针 j
                // 注意：主串指针 i 不回溯
                j = next[j - 1];
            } else {
                // 如果模式串的第一个字符就不匹配，主串指针后移
                i++;
            }
        }
    }

    return -1; // 未找到匹配
}

int bf(const std::string &text, const std::string &pattern) {
}

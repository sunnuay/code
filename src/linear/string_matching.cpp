#include "linear.hpp"
#include <cstddef>
#include <print>
#include <vector>

void StringMatching::bf() {
  size_t i = 0, j = 0;
  while (i < txt.size() && j < pat.size())
    if (txt[i] == pat[j])
      i++, j++;
    else
      i = i - j + 1, j = 0;
  std::println("BF: {}", j == pat.size() ? i - j : -1);
}

void StringMatching::kmp() {
  std::vector<int> lps = pf();
  size_t i = 0, j = 0;
  while (i < txt.size() && j < pat.size())
    if (txt[i] == pat[j])
      i++, j++;
    else if (j)
      j = lps[j - 1];
    else
      i++;
  std::println("KMP: {}", j == pat.size() ? i - j : -1);
}

std::vector<int> StringMatching::pf() {
  std::vector<int> lps(pat.size());
  size_t i = 1, j = 0;
  while (i < pat.size())
    if (pat[i] == pat[j])
      lps[i] = j + 1, i++, j++;
    else if (j)
      j = lps[j - 1];
    else
      i++;
  return lps;
}

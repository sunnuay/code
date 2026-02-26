#include "linear.hpp"
#include <print>

void StringMatching::bf() {
  int i = 0, j = 0;
  while (i < txt.size() && j < pat.size())
    if (txt[i] == pat[j])
      i++, j++;
    else
      i = i - j + 1, j = 0;
  std::println("BF: {}", j == pat.size() ? i - j : -1);
}

void StringMatching::kmp() {
  std::vector<int> lps = pf();
  int i = 0, j = 0;
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
  int i = 1, j = 0;
  while (i < pat.size())
    if (pat[i] == pat[j])
      lps[i] = j + 1, i++, j++;
    else if (j)
      j = lps[j - 1];
    else
      i++;
  return lps;
}

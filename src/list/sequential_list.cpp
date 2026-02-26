#include "list.hpp"
#include <print>

SequentialList::SequentialList() { size = 0; }

void SequentialList::print() {
  for (int i = 0; i < size; i++)
    std::print("{} ", data[i]);
  std::println();
}

bool SequentialList::insert(int val, int idx) {
  if (size >= MAX || idx < 0 || idx > size)
    return false;
  for (int i = size; i > idx; i--)
    data[i] = data[i - 1];
  data[idx] = val;
  size++;
  return true;
}

bool SequentialList::insert(int val) { return insert(val, size); }

bool SequentialList::remove(int idx) {
  if (idx < 0 || idx >= size)
    return false;
  for (int i = idx; i < size - 1; i++)
    data[i] = data[i + 1];
  size--;
  return true;
}

bool SequentialList::remove() { return remove(size - 1); }

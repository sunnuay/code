#include "list.hpp"

template <typename List> void test() {
  List list;
  list.insert(1);
  list.insert(2);
  list.insert(3, 0);
  list.insert(4, 1);
  list.remove(1);
  list.remove();
  list.print();
}

int main() {
  test<SequentialList>();
  test<SinglyLinkedList>();
  test<CircularLinkedList>();
  test<DoublyLinkedList>();
  test<StaticLinkedList>();
}

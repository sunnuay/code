#include "list.h"

template <typename List>
void test() {
    List list;
    list.insert(1);
    list.insert(2, 0);
    list.insert(3, 1);
    list.erase(0);
    list.erase();
    list.print();
}

int main() {
    test<SequentialList>();
    test<SinglyLinkedList>();
    test<CircularLinkedList>();
    test<DoublyLinkedList>();
    test<StaticLinkedList>();
}

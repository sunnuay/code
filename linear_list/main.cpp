#include "linear_list.h"

template <typename List>
void test() {
    List list;
    list.insert(1);
    list.insert(2, 0);
    list.insert(3, 1);
    list.print();
    list.erase(list.find(3));
    list.erase(0);
    list.erase();
}

int main() {
    test<SequentialList>();
    test<SinglyLinkedList>();
    test<CircularLinkedList>();
    test<DoublyLinkedList>();
    test<StaticLinkedList>();
}

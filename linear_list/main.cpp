#include "linear_list.h"

int main() {
    SinglyLinkedList list;
    list.insert(114);
    list.insert(0, 514);
    list.erase(list.find(514));
    list.print();
}
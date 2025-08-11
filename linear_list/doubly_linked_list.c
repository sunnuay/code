typedef struct DoublyLinkedNode
{
    int data;
    struct DoublyLinkedNode *prior;
    struct DoublyLinkedNode *next;
} DoublyLinkedNode, *DoublyLinkedList;

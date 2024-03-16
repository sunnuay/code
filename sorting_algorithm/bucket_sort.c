#include <stdio.h>
#include <stdlib.h>
#define BUCKET_NUM 10

struct ListNode
{
    int mData;
    struct ListNode *mNext;
};

struct ListNode *createNode(int data)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    newNode->mData = data;
    newNode->mNext = NULL;
    return newNode;
}

struct ListNode *insert(struct ListNode *head, int val)
{
    struct ListNode dummyNode;
    struct ListNode *newNode = createNode(val);
    struct ListNode *pre = &dummyNode;
    struct ListNode *curr = head;
    dummyNode.mNext = head;

    while (curr != NULL && curr->mData <= val)
    {
        pre = curr;
        curr = curr->mNext;
    }

    newNode->mNext = curr;
    pre->mNext = newNode;
    return dummyNode.mNext;
}

struct ListNode *Merge(struct ListNode *head1, struct ListNode *head2)
{
    struct ListNode dummyNode;
    struct ListNode *dummy = &dummyNode;
    dummyNode.mNext = NULL;

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->mData <= head2->mData)
        {
            dummy->mNext = head1;
            head1 = head1->mNext;
        }
        else
        {
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }

    if (head1 != NULL)
        dummy->mNext = head1;
    if (head2 != NULL)
        dummy->mNext = head2;

    return dummyNode.mNext;
}

void bucket_sort(int arr[], int len)
{
    struct ListNode *buckets[BUCKET_NUM];
    for (int i = 0; i < BUCKET_NUM; i++)
        buckets[i] = NULL;

    for (int i = 0; i < len; i++)
    {
        int index = arr[i] / BUCKET_NUM;
        buckets[index] = insert(buckets[index], arr[i]);
    }

    struct ListNode *head = buckets[0];
    for (int i = 1; i < BUCKET_NUM; i++)
    {
        head = Merge(head, buckets[i]);
    }

    int j = 0;
    struct ListNode *temp = head;
    while (temp != NULL)
    {
        arr[j++] = temp->mData;
        temp = temp->mNext;
    }
}

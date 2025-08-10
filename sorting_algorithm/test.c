#include <stdio.h>

void insertion_sort(int[], int);
void shell_sort(int[], int);
void selection_sort(int[], int);
void bubble_sort(int[], int);
void quick_sort(int[], int);
void heap_sort(int[], int);
void merge_sort(int[], int);
void counting_sort(int[], int);
void bucket_sort(int[], int);
void radix_sort(int[], int);

void (*sort[])(int[], int) = {
    insertion_sort, shell_sort, selection_sort, bubble_sort, quick_sort, heap_sort, merge_sort, counting_sort, bucket_sort, radix_sort};

int main()
{
    for (int i = 0; i < 10; i++)
    {
        int arr[] = {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6};
        int len = sizeof(arr) / sizeof(int);
        sort[i](arr, len);
        for (int j = 0; j < len; j++)
            printf("%d ", arr[j]);
        printf("\n");
    }
}

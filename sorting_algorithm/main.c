#include <stdio.h>

void bubble_sort(int arr[], int len);
void quick_sort(int arr[], int len);
void insertion_sort(int arr[], int len);
void shell_sort(int arr[], int len);
void selection_sort(int arr[], int len);
void heap_sort(int arr[], int len);

int main()
{
    int arr[] = {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6};
    int len = sizeof(arr) / sizeof(int);

    heap_sort(arr, len);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    return 0;
}

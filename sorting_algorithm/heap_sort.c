#include "sorting_algorithm.h"

void heap(int arr[], int len, int i) {
    int max = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < len && arr[max] < arr[l])
        max = l;
    if (r < len && arr[max] < arr[r])
        max = r;
    if (max != i)
        swap(arr, i, max), heap(arr, len, max);
}

void heap_sort(int arr[], int len) {
    for (int i = len / 2 - 1; i >= 0; i--)
        heap(arr, len, i);
    for (int i = len - 1; i > 0; i--)
        swap(arr, 0, i), heap(arr, i, 0);
}

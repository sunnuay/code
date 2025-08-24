#include "sorting_algorithm.h"

void quick(int arr[], int l, int r) {
    if (l >= r)
        return;
    int mid = arr[(l + r) / 2], i = l, j = r;
    while (i <= j) {
        while (arr[i] < mid)
            i++;
        while (arr[j] > mid)
            j--;
        if (i <= j)
            swap(arr, i, j), i++, j--;
    }
    quick(arr, l, j);
    quick(arr, i, r);
}

void quick_sort(int arr[], int len) {
    quick(arr, 0, len - 1);
}

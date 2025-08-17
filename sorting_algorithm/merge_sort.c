#include "sort.h"

void merge(int arr[], int tmp[], int l, int r)
{
    if (l >= r)
        return;
    int m = (l + r) / 2;
    merge(arr, tmp, l, m);
    merge(arr, tmp, m + 1, r);
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r)
        tmp[k++] = arr[i] <= arr[j] ? arr[i++] : arr[j++];
    while (i <= m)
        tmp[k++] = arr[i++];
    while (j <= r)
        tmp[k++] = arr[j++];
    for (i = l; i <= r; i++)
        arr[i] = tmp[i];
}

void merge_sort(int arr[], int len)
{
    int tmp[len];
    merge(arr, tmp, 0, len - 1);
}

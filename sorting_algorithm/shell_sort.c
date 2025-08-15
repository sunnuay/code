#include "sorting_algorithm.h"

void shell_sort(int arr[], int len)
{
    int n = 3, gap[] = {1, 3, 5};
    while (n--)
        for (int h = gap[n], i = h; i < len; i++)
            for (int j = i; j >= h; j -= h)
                if (arr[j - h] > arr[j])
                    swap(arr, j - h, j);
                else
                    break;
}

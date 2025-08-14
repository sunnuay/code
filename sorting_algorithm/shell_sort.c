#include "sorting_algorithm.h"

void shell_sort(int arr[], int len)
{
    int gap[] = {1, 3, 5};
    int n = sizeof(gap) / sizeof(int);
    while (n--)
        for (int h = gap[n], i = h; i < len; i++)
            for (int j = i; j >= h; j -= h)
                if (arr[j - h] > arr[j])
                    swap(&arr[j - h], &arr[j]);
                else
                    break;
}

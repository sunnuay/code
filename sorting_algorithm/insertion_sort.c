#include "sort.h"

void insertion_sort(int arr[], int len)
{
    for (int i = 1; i < len; i++)
    {
        int j, key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
}

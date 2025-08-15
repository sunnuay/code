#include "sorting_algorithm.h"

void swap(int arr[], int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int get_max(int arr[], int len)
{
    int tmp = arr[0];
    for (int i = 1; i < len; i++)
        if (arr[i] > tmp)
            tmp = arr[i];
    return tmp;
}

int get_min(int arr[], int len)
{
    int tmp = arr[0];
    for (int i = 1; i < len; i++)
        if (arr[i] < tmp)
            tmp = arr[i];
    return tmp;
}

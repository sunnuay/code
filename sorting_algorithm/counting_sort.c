#include "sorting_algorithm.h"

void counting_sort(int arr[], int len)
{
    int MIN = 0, MAX = 99;
    int num = 100;
    int cnt[num], tmp[len];
    for (int i = 0; i < num; i++)
        cnt[i] = 0;
    for (int i = 0; i < len; i++)
        cnt[arr[i]]++;
    for (int i = 1; i < num; i++)
        cnt[i] += cnt[i - 1];
    for (int i = len - 1; i >= 0; i--)
        tmp[--cnt[arr[i]]] = arr[i];
    for (int i = 0; i < len; i++)
        arr[i] = tmp[i];
}

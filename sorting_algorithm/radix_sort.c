#include "sorting_algorithm.h"
#define N 10

void radix_sort(int arr[], int len)
{
    int max = get_max(arr, len);
    int tmp[len];
    for (int exp = 1; max / exp > 0; exp *= N)
    {
        int cnt[N] = {0};
        for (int i = 0; i < len; i++)
            cnt[(arr[i] / exp) % N]++;
        for (int i = 1; i < N; i++)
            cnt[i] += cnt[i - 1];
        for (int i = len - 1; i >= 0; i--)
            tmp[--cnt[(arr[i] / exp) % N]] = arr[i];
        for (int i = 0; i < len; i++)
            arr[i] = tmp[i];
    }
}

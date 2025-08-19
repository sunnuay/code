#include "sort.h"

void radix_sort(int arr[], int len) {
    int MIN = 0, MAX = 99;
    int num = 10;
    int cnt[num], tmp[len];
    for (int exp = 1; exp <= MAX; exp *= num) {
        for (int i = 0; i < num; i++)
            cnt[i] = 0;
        for (int i = 0; i < len; i++)
            cnt[(arr[i] / exp) % num]++;
        for (int i = 1; i < num; i++)
            cnt[i] += cnt[i - 1];
        for (int i = len - 1; i >= 0; i--)
            tmp[--cnt[(arr[i] / exp) % num]] = arr[i];
        for (int i = 0; i < len; i++)
            arr[i] = tmp[i];
    }
}

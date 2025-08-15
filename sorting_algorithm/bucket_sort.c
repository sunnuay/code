#include "sorting_algorithm.h"
#define N 10

void bucket_sort(int arr[], int len)
{
    int max = get_max(arr, len);
    int min = get_min(arr, len);
    int gap = (max - min) / N + 1;
    int bkt[N][len], cnt[N] = {0};
    for (int i = 0; i < len; i++)
    {
        int n = (arr[i] - min) / gap;
        bkt[n][cnt[n]++] = arr[i];
    }
    for (int k = 0, i = 0; i < N; i++)
    {
        insertion_sort(bkt[i], cnt[i]);
        for (int j = 0; j < cnt[i]; j++)
            arr[k++] = bkt[i][j];
    }
}

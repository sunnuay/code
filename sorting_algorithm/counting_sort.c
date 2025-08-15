#include "sorting_algorithm.h"

void counting_sort(int arr[], int len)
{
    int max = get_max(arr, len);
    int min = get_min(arr, len);
    int ran = max - min + 1;
    int tmp[ran];
    for (int i = 0; i < ran; i++)
        tmp[i] = 0;
    for (int i = 0; i < len; i++)
        tmp[arr[i] - min]++;
    for (int i = 0, j = 0; i < ran; i++)
        while (tmp[i]--)
            arr[j++] = i + min;
}

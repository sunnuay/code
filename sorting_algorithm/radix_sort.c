#include <stdlib.h>

int maxbit(int arr[], int len)
{
    int maxData = arr[0];

    for (int i = 1; i < len; ++i)
    {
        if (maxData < arr[i])
            maxData = arr[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}

void radix_sort(int arr[], int len)
{
    int d = maxbit(arr, len);
    int *tmp = (int *)malloc(len * sizeof(int));
    int *count = (int *)malloc(10 * sizeof(int));
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)
    {
        for (j = 0; j < 10; j++)
            count[j] = 0;
        for (j = 0; j < len; j++)
        {
            k = (arr[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = len - 1; j >= 0; j--)
        {
            k = (arr[j] / radix) % 10;
            tmp[count[k] - 1] = arr[j];
            count[k]--;
        }
        for (j = 0; j < len; j++)
            arr[j] = tmp[j];
        radix = radix * 10;
    }
    free(tmp);
    free(count);
}

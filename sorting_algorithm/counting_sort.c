#include <stdlib.h>
void counting_sort(int arr[], int len)
{
    int maxValue = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
        }
    }

    int bucketLen = maxValue + 1;
    int *bucket = (int *)calloc(bucketLen, sizeof(int));

    for (int i = 0; i < len; i++)
    {
        bucket[arr[i]]++;
    }

    int sortedIndex = 0;
    for (int j = 0; j < bucketLen; j++)
    {
        while (bucket[j] > 0)
        {
            arr[sortedIndex] = j;
            sortedIndex++;
            bucket[j]--;
        }
    }

    free(bucket);
}

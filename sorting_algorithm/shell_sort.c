void shell_sort(int arr[], int len)
{
    int j;
    for (int gap = len >> 1; gap > 0; gap >>= 1)
        for (int i = gap; i < len; i++)
        {
            int key = arr[i];
            for (j = i - gap; j >= 0 && arr[j] > key; j -= gap)
                arr[j + gap] = arr[j];
            arr[j + gap] = key;
        }
}

void swap(int *a, int *b);

void shell_sort(int arr[], int len)
{
    int gaps[] = {5, 3, 1};
    int size = sizeof(gaps) / sizeof(int);
    for (int n = 0; n < size; n++)
    {
        int h = gaps[n];
        for (int i = h; i < len; i++)
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h)
                swap(&arr[j], &arr[j - h]);
    }
}

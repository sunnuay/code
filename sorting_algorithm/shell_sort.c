void swap(int *a, int *b);

void shell_sort(int arr[], int len)
{
    int gap[] = {1, 3, 5};
    int n = sizeof(gap) / sizeof(int);
    while (n)
    {
        int h = gap[--n];
        for (int i = h; i < len; i++)
            for (int j = i; j >= h && arr[j - h] > arr[j]; j -= h)
                swap(&arr[j - h], &arr[j]);
    }
}

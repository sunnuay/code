void swap(int *, int *);

void heap(int arr[], int dad, int end)
{
    int son = dad * 2 + 1;
    while (son <= end)
    {
        if (son < end && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] < arr[son])
        {
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
        else
            return;
    }
}

void heap_sort(int arr[], int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
        heap(arr, i, len - 1);
    for (int i = len - 1; i > 0; i--)
        swap(&arr[0], &arr[i]), heap(arr, 0, i - 1);
}

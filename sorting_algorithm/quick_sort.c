void swap(int *a, int *b);

void partition(int arr[], int l, int r)
{
    if (l >= r)
        return;
    int mid = arr[(l + r) / 2], i = l, j = r;
    while (i <= j)
    {
        while (arr[i] < mid)
            i++;
        while (arr[j] > mid)
            j--;
        if (i <= j)
            swap(&arr[i], &arr[j]), i++, j--;
    }
    partition(arr, l, j);
    partition(arr, i, r);
}

void quick_sort(int arr[], int len)
{
    partition(arr, 0, len - 1);
}

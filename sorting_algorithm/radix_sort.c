void radix_sort(int arr[], int len)
{
    int max = arr[0];
    for (int i = 1; i < len; i++)
        if (arr[i] > max)
            max = arr[i];
    int tmp[len];
    for (int exp = 1; max / exp > 0; exp *= 10)
    {
        int cnt[10] = {0};
        for (int i = 0; i < len; i++)
            cnt[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++)
            cnt[i] += cnt[i - 1];
        for (int i = len - 1; i >= 0; i--)
            tmp[--cnt[(arr[i] / exp) % 10]] = arr[i];
        for (int i = 0; i < len; i++)
            arr[i] = tmp[i];
    }
}

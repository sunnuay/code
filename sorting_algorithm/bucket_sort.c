void insertion_sort(int[], int);

void bucket_sort(int arr[], int len)
{
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i++)
        if (arr[i] > max)
            max = arr[i];
        else if (arr[i] < min)
            min = arr[i];
    const int num = 10;
    int gap = (max - min) / num + 1;
    int bkt[num][len], cnt[num] = {0};
    for (int i = 0; i < len; i++)
    {
        int n = (arr[i] - min) / gap;
        bkt[n][cnt[n]++] = arr[i];
    }
    for (int k = 0, i = 0; i < num; i++)
    {
        insertion_sort(bkt[i], cnt[i]);
        for (int j = 0; j < cnt[i]; j++)
            arr[k++] = bkt[i][j];
    }
}

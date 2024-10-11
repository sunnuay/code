void insertion_sort(int arr[], int len);

void bucket_sort(int arr[], int len)
{
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    int num = 10;
    int gap = (max - min) / num + 1;
    int bkt[num][len];
    int cnt[num];
    for (int i = 0; i < num; i++)
        cnt[i] = 0;
    for (int i = 0; i < len; i++)
        bkt[(arr[i] - min) / gap][cnt[(arr[i] - min) / gap]++] = arr[i];
    for (int i = 0; i < num; i++)
        insertion_sort(bkt[i], cnt[i]);
    for (int i = 0, k = 0; i < num; i++)
        for (int j = 0; j < cnt[i]; j++)
            arr[k++] = bkt[i][j];
}

void counting_sort(int arr[], int len)
{
    int max = arr[0], min = arr[0];
    for (int i = 1; i < len; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
    int ran = max - min + 1;
    int tmp[ran];
    for (int i = 0; i < ran; i++)
        tmp[i] = 0;
    for (int i = 0; i < len; i++)
        tmp[arr[i] - min]++;
    for (int i = 0, j = 0; i < ran; i++)
        while (tmp[i]--)
            arr[j++] = i + min;
}

#include <stdio.h>
#include <string.h>

void bubble_sort(int arr[], int len);
void quick_sort(int arr[], int len);
void insertion_sort(int arr[], int len);
void shell_sort(int arr[], int len);
void selection_sort(int arr[], int len);
void heap_sort(int arr[], int len);
void merge_sort(int arr[], int len);

int main()
{
    int arr[] = {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6};
    int len = sizeof(arr) / sizeof(int);

    int n = 7;
    int arrs[n][sizeof(arr)];
    for (int i = 0; i < n; i++)
        memcpy(arrs[i], arr, sizeof(arr));

    bubble_sort(arrs[0], len);
    quick_sort(arrs[1], len);
    insertion_sort(arrs[2], len);
    shell_sort(arrs[3], len);
    selection_sort(arrs[4], len);
    heap_sort(arrs[5], len);
    merge_sort(arrs[6], len);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < len; j++)
            printf("%2d ", arrs[i][j]);
        printf("\n");
    }

    return 0;
}

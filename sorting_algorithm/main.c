#include <stdio.h>
#include <string.h>
#define ARR {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6}
#define LEN 15
#define N 10

void bubble_sort(int arr[], int len);
void quick_sort(int arr[], int len);
void insertion_sort(int arr[], int len);
void shell_sort(int arr[], int len);
void selection_sort(int arr[], int len);
void heap_sort(int arr[], int len);
void merge_sort(int arr[], int len);
void counting_sort(int arr[], int len);
void radix_sort(int arr[], int len);
void bucket_sort(int arr[], int len);

void (*sort[])(int[], int) = {
    bubble_sort,
    quick_sort,
    insertion_sort,
    shell_sort,
    selection_sort,
    heap_sort,
    merge_sort,
    counting_sort,
    radix_sort,
    bucket_sort};

int main()
{
    int arrs[N][LEN] = {ARR};
    for (int i = 1; i < N; i++)
        memcpy(arrs[i], arrs[0], sizeof(int) * LEN);

    for (int i = 0; i < N; i++)
    {
        sort[i](arrs[i], LEN);
        for (int j = 0; j < LEN; j++)
            printf("%2d ", arrs[i][j]);
        printf("\n");
    }
    return 0;
}

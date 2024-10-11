#include <stdio.h>

#define ARR {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6}
#define LEN 15
#define N 10

void bubble_sort(int[], int);
void quick_sort(int[], int);
void insertion_sort(int[], int);
void shell_sort(int[], int);
void selection_sort(int[], int);
void heap_sort(int[], int);
void merge_sort(int[], int);
void counting_sort(int[], int);
void radix_sort(int[], int);
void bucket_sort(int[], int);

void (*sort[])(int[], int) = {
    bubble_sort, quick_sort, insertion_sort, shell_sort, selection_sort,
    heap_sort, merge_sort, counting_sort, radix_sort, bucket_sort};

int main()
{
    for (int i = 0; i < N; i++)
    {
        int arr[] = ARR;
        sort[i](arr, LEN);
        for (int j = 0; j < LEN; j++)
            printf("%2d ", arr[j]);
        printf("\n");
    }
}

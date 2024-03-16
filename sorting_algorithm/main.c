#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int arr[], int len);    // 冒泡排序
void selection_sort(int arr[], int len); // 选择排序
void insertion_sort(int arr[], int len); // 插入排序
void shell_sort(int arr[], int len);     // 希尔排序
void merge_sort(int arr[], int len);     // 归并排序
void quick_sort(int arr[], int len);     // 快速排序
void heap_sort(int arr[], int len);      // 堆排序
void counting_sort(int arr[], int len);  // 计数排序
void bucket_sort(int arr[], int len);    // 桶排序
void radix_sort(int arr[], int len);     // 基数排序

int main()
{
    int len = 10;
    int arr[10];

    srand(time(NULL));
    for (int i = 0; i < len; i++)
        arr[i] = rand() % 100;

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");

    radix_sort(arr, len);

    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
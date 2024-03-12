#include <iostream>

void bubble_sort(int arr[], int len); // 冒泡排序
void selection_sort();                // 选择排序
void insertion_sort();                // 插入排序
void shell_sort();                    // 希尔排序
void merge_sort();                    // 归并排序
void quick_sort();                    // 快速排序
void heap_sort();                     // 堆排序
void counting_sort();                 // 计数排序
void bucket_sort();                   // 桶排序
void radix_sort();                    // 基数排序

int main()
{
    int len = 10;
    int arr[10];

    srand(time(NULL));
    for (int i = 0; i < len; i++)
        arr[i] = rand() % 100;

    for (int i = 0; i < len; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    bubble_sort(arr, len);

    for (int i = 0; i < len; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}

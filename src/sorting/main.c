#include "sorting.h"
#include <stdio.h>
#include <string.h>

int main() {
  void (*sort[])(int[], int) = {
      insertion_sort, shell_sort, selection_sort, bubble_sort, quick_sort,
      heap_sort,      merge_sort, counting_sort,  bucket_sort, radix_sort};
  int data[] = {5, 12, 15, 11, 3, 8, 13, 9, 4, 7, 10, 2, 14, 1, 6};
  int num = sizeof(sort) / sizeof(*sort);
  int len = sizeof(data) / sizeof(*data);
  for (int i = 0; i < num; i++) {
    int arr[len];
    memcpy(arr, data, sizeof(data));
    sort[i](arr, len);
    for (int j = 0; j < len; j++)
      printf("%d ", arr[j]);
    printf("\n");
  }
}

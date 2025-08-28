#include "sorting.h"

void selection_sort(int arr[], int len) {
    for (int i = len - 1; i > 0; i--) {
        int max = i;
        for (int j = 0; j < i; j++)
            if (arr[j] > arr[max])
                max = j;
        swap(arr, max, i);
    }
}

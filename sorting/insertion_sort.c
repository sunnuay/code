#include "sorting.h"

void insertion_sort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int j, key = arr[i];
        for (j = i; j > 0; j--)
            if (arr[j - 1] > key)
                arr[j] = arr[j - 1];
            else
                break;
        arr[j] = key;
    }
}

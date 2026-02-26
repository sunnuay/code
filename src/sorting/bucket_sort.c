#include "sorting.h"

void bucket_sort(int arr[], int len) {
  int MIN = 0, MAX = 99;
  int num = 10, gap = 10;
  int cnt[num], tmp[num][len];
  for (int i = 0; i < num; i++)
    cnt[i] = 0;
  for (int i = 0; i < len; i++)
    tmp[arr[i] / gap][cnt[arr[i] / gap]++] = arr[i];
  for (int i = 0; i < num; i++)
    insertion_sort(tmp[i], cnt[i]);
  for (int n = 0, i = 0; i < num; i++)
    for (int j = 0; j < cnt[i]; j++)
      arr[n++] = tmp[i][j];
}

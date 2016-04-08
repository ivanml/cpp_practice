#include <iostream>
#include "print.h"

using namespace std;

int partition(vector<int> &nums, int i, int j) {
  int pivot = nums[i + (j - i) / 2];

  while (i <= j) {    
    while (nums[i] < pivot)
      i ++;
    while (nums[j] > pivot)
      j --;
    
    if (i <= j) {
      // swap
      int t = nums[i];
      nums[i] = nums[j];
      nums[j] = t;
      i ++;
      j --;
    }
  }

  return i;
}

void quicksort(vector<int> &nums, int i, int j) {
  if (nums.empty() || i >= j)
    return;

  int index = partition(nums, i, j);
  if (index > i)
    quicksort(nums, i, index - 1);
  if (index < j)
    quicksort(nums, index, j);
}

int main() {
  vector<int> nums = {4, 1, 6, 3, 5, 7, 2};
  print(nums);

  quicksort(nums, 0, nums.size() - 1);
  print(nums);

  return 0;
}

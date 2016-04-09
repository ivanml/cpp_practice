#include <iostream>
#include "print.h"

using namespace std;

int partition(vector<int> &nums, int left, int right) {
  int pivot = nums[left];
  int l = left + 1; // starting from second element
  int r = right;

  while (l <= r) {
    if (nums[l] > pivot && nums[r] < pivot)
      swap(nums[l++], nums[r--]);
    
    while (l <= r && nums[l] <= pivot) l ++;
    while (l <= r && nums[r] >= pivot) r --;
  }
  
  // put pivot in its correct pos, which is r
  swap(nums[r], nums[left]);
  return r;
}

void quicksort(vector<int> &nums, int left, int right) {
  if (left < right) {
    int pivotIndex = partition(nums, left, right);

    if (pivotIndex - 1 > left)
      quicksort(nums, left, pivotIndex - 1);
    if (pivotIndex + 1 < right)
      quicksort(nums, pivotIndex + 1, right);
  }
}

int main() {
  vector<int> nums = {8, 3, 1, 5, 4, 2, 7, 6, 9, 5, 1, 2, 6, 4, 0, 0, 1, 4, 5, 5, 5, 3, 2, 9};
  cout << "input nums: ";
  print(nums);

  quicksort(nums, 0, nums.size() - 1);
  cout << "sorted nums: ";
  print(nums);

  return 0;
}

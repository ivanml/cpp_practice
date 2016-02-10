#include <iostream>
#include "print.h"

using namespace std;

int main() {
  // easier way to initialize a vector
  static const int arr[] = {16,2,77,29};
  vector<int> nums(arr, arr + sizeof(arr) / sizeof(arr[0]) );

  print(nums);

  return 0;
}

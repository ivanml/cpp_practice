#ifndef _PRINT_H_
#define _PRINT_H_
#include <vector>

template <class T>
void print(const std::vector<T> &v, bool newline = true) {
  std::cout << "[";
  for (int i = 0; i < v.size(); ++ i) {
    std::cout << v[i];
    if (i < v.size() - 1)
      std::cout << ", ";
  }
  std::cout << "]";
  if (newline)
    std::cout << std::endl;
}

template <class T>
void print_vv(const std::vector<std::vector<T> > &vv,
              bool vertical = false) {
  std::cout << "[";
  for (int i = 0; i < vv.size(); ++ i) {
    if (vertical)
      std::cout << std::endl << " ";
    print(vv[i], false);
    if (i < vv.size() - 1)
      std::cout << ", ";
  }
  if (vertical)
    std::cout << std::endl;
  std::cout << "]" << std::endl;
}

#endif

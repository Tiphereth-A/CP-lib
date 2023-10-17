#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_6_A"

#include "../../code/fast/rsort32.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> a(n);
  for (auto& i : a) std::cin >> i;
  tifa_libs::rsort32(a);
  for (size_t i = 0; i < n; ++i) std::cout << a[i] << " \n"[i == n - 1];
  return 0;
}

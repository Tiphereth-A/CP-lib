#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"

#include "../../code/util/hash_splitmix64.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::hset<tifa_libs::u64> dict;
  for (size_t i = 0; i < n; ++i) {
    std::string s, t;
    std::cin >> s >> t;
    tifa_libs::u64 x = 0;
    for (char c : t) switch (c) {
        case 'A':
          ++x;
        case 'C':
          ++x;
        case 'G':
          ++x;
        default:
          (++x) *= 5;
      }
    if (s[0] == 'i')
      dict.insert(x);
    else
      std::cout << (dict.count(x) ? "yes\n" : "no\n");
  }
  return 0;
}

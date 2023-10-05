#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_4_C"

#include "../../code/util/hash_splitmix64.hpp"

int main() {
  tifa_libs::util::hash_splitmix64::set_seed((tifa_libs::u64)std::chrono::steady_clock::now().time_since_epoch().count());
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(10);
  tifa_libs::u32 n;
  std::cin >> n;
  tifa_libs::util::hset<std::string> dict;
  for (size_t i = 0; i < n; ++i) {
    std::string s, t;
    std::cin >> s >> t;
    if (s[0] == 'i')
      dict.insert(t);
    else
      std::cout << (dict.count(t) ? "yes\n" : "no\n");
  }
  return 0;
}

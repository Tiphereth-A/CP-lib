#define PROBLEM "https://www.luogu.com.cn/problem/P3809"

#include "../../code/str/suffix_array.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  s = " " + s;
  auto [sa, rk] = tifa_libs::str::suffixsort(s);
  for(size_t i = 1; i < s.size(); ++ i) std::cout << sa[i] << " \n"[i + 1 == s.size()];
  return 0;
}

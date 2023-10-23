#define PROBLEM "https://www.luogu.com.cn/problem/P3804"

#include "../../code/str/suffix_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string s;
  std::cin >> s;
  tifa_libs::str::suffix_automaton sam;
  for (auto c : s) sam.extend(u32(c - 'a'));
  u64 ans = 0;
  sam.build(), sam.gettimes();
  for (size_t i = 1; i < sam.sz; ++i)
    if (sam.st[i].times > 1) ans = std::max(ans, (u64)sam.st[i].times * sam.st[i].len);
  std::cout << ans;
  return 0;
}

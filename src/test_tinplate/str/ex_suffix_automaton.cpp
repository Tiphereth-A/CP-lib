#define PROBLEM "https://www.luogu.com.cn/problem/P6139"

#include "../../code/str/ex_suffix_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n;
  std::string s;
  std::cin >> n;
  tifa_libs::str::ex_suffix_automaton sam;
  for (size_t i = 0; i < n; ++i) std::cin >> s, sam.insert(s);
  sam.build();
  size_t ans = 0;
  for (size_t i = 1; i < sam.sz; ++i) ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n'
            << sam.sz;
  return 0;
}
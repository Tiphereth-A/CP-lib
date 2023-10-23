#define PROBLEM "https://www.luogu.com.cn/problem/P6139"

#include "../../code/str/orthodox_ex_suffix_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  usz n;
  std::string s;
  std::cin >> n;
  tifa_libs::str::orthodox_ex_suffix_automaton sam;
  for (usz i = 0; i < n; ++i) std::cin >> s, sam.insert(s);
  sam.build();
  usz ans = 0;
  for (usz i = 1; i < sam.sz; ++i) ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n'
            << sam.sz;
  return 0;
}
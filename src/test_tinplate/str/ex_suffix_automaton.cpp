#define PROBLEM "https://www.luogu.com.cn/problem/P6139"

#include "../../code/str/ex_suffix_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::string s;
  std::cin >> n;
  tifa_libs::str::ex_suffix_automaton sam;
  for (u32 i = 0; i < n; ++i) {
    std::cin >> s;
    u32 last = 0;
    for (auto c : s)
      last = sam.extend(last, u32(c - 'a'));
  }
  u64 ans = 0;
  for (u32 i = 1; i < sam.sz; ++i) ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n'
            << sam.sz;
  return 0;
}
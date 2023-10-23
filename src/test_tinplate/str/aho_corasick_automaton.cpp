#define PROBLEM "https://www.luogu.com.cn/problem/P5357"

#include "../../code/str/aho_corasick_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n;
  std::string s;
  std::cin >> n;
  tifa_libs::vec<tifa_libs::u32> ans(n);
  tifa_libs::str::aho_corasick_automaton acam;
  for (tifa_libs::u32 i = 0; i < n; ++i) std::cin >> s, acam.insert(s, i);
  acam.getfail();
  std::cin >> s;
  tifa_libs::vec<tifa_libs::u32> sz(acam.sz), in(acam.sz);
  for (tifa_libs::u32 i = 0, u = 0; i < s.size(); ++i) u = acam.t[u].nex[tifa_libs::u32(s[i] - 'a')], sz[u] += 1;
  for (tifa_libs::u32 i = 0; i < acam.sz; ++i) ++in[acam.t[i].fail];
  std::queue<tifa_libs::u32> q;
  for (tifa_libs::u32 i = 0; i < acam.sz; ++i)
    if (!in[i]) q.push(i);
  while (!q.empty()) {
    tifa_libs::u32 u = q.front();
    q.pop();
    for (auto x : acam.t[u].end) ans[x] = sz[u];
    tifa_libs::u32 v = acam.t[u].fail;
    sz[v] += sz[u];
    --in[v];
    if (!in[v]) q.push(v);
  }
  for (auto x : ans) std::cout << x << ' ';
  return 0;
}
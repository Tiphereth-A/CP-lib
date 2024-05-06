#define PROBLEM "https://www.luogu.com.cn/problem/P5357"

#include "../../code/str/aho_corasick_automaton.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  strn s;
  std::cin >> n;
  vecu ans(n);
  tifa_libs::str::aho_corasick_automaton acam;
  flt_ (u32, i, 0, n) std::cin >> s, acam.insert(s, i);
  acam.getfail();
  std::cin >> s;
  vecu sz(acam.sz), in(acam.sz);
  for (u32 i = 0, u = 0; i < s.size(); ++i) u = acam.t[u].nex[u32(s[i] - 'a')], sz[u] += 1;
  for (u32 i = 0; i < acam.sz; ++i) ++in[acam.t[i].fail];
  std::queue<u32> q;
  for (u32 i = 0; i < acam.sz; ++i)
    if (!in[i]) q.push(i);
  while (!q.empty()) {
    u32 u = q.front();
    q.pop();
    for (auto x : acam.t[u].end) ans[x] = sz[u];
    u32 v = acam.t[u].fail;
    sz[v] += sz[u];
    --in[v];
    if (!in[v]) q.push(v);
  }
  for (auto x : ans) std::cout << x << '\n';
  return 0;
}

/*
给你一个文本串 $S$ 和 $n$ 个模式串 $T_{1 \sim n}$, 请你分别求出每个模式串 $T_i$ 在 $S$ 中出现的次数

## 输入
第一行包含一个正整数 $n$ 表示模式串的个数
接下来 $n$ 行, 第 $i$ 行包含一个由小写英文字母构成的非空字符串 $T_i$
最后一行包含一个由小写英文字母构成的非空字符串 $S$
数据不保证任意两个模式串不相同

## 输出
输出包含 $n$ 行, 其中第 $i$ 行包含一个非负整数表示 $T_i$ 在 $S$ 中出现的次数
*/

/*
5
a
bb
aa
abaa
abaaa
abaaabaa
============
6
0
3
2
1
*/
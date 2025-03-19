#define PROBLEM "https://www.luogu.com.cn/problem/P6139"

#include "../../include/str/orthodox_ex_suffix_automaton.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  strn s;
  std::cin >> n;
  tifa_libs::str::orthodox_ex_suffix_automaton sam;
  flt_ (u32, i, 0, n) std::cin >> s, sam.insert(s);
  sam.build();
  u64 ans = 0;
  for (u32 i = 1; i < sam.sz; ++i) ans += sam.st[i].len - sam.st[sam.st[i].link].len;
  std::cout << ans << '\n'
            << sam.sz;
}

/*
给定 $n$ 个由小写字母组成的字符串 $s_1,s_2\ldots s_n$, 求本质不同的子串个数. (不包含空串)
进一步, 设 $Q$ 为能接受 $s_1,s_2,\dots,s_n$ 的所有后缀的最小 DFA, 请你输出 $Q$ 的点数. (如果你无法理解这句话, 可以认为就是输出 $s_1,s_2,\dots,s_n$ 建成的 "广义后缀自动机" 的点数)

## 输入
第一行一个正整数 $n$
以下 $n$ 行, 每行一个字符串, 第 $i$ 行表示字符串 $s_{i-1}$

## 输出
第一行一个正整数, 为本质不同的子串个数
第二行一个正整数, 为 $Q$ 的点数
*/

/*
4
aa
ab
bac
caa
==========
10
10
*/

/*
1
a
=========
1
2
*/
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
  for (usz i = 1; i < sam.sz; ++i)
    if (sam.st[i].times > 1) ans = std::max(ans, (u64)sam.st[i].times * sam.st[i].len);
  std::cout << ans;
  return 0;
}

/*
给定一个只包含小写字母的字符串 $S$

请你求出 $S$ 的所有出现次数不为 $1$ 的子串的出现次数乘上该子串长度的最大值

## 输入格式

一行一个仅包含小写字母的字符串 $S$

## 输出格式

一个整数, 为所求答案
*/

/*
abab
============
4
*/
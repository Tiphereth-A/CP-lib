#define PROBLEM "https://www.luogu.com.cn/problem/P3809"

#include "../../code/str/suffix_array.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  strn s;
  std::cin >> s;
  s = " " + s;
  tifa_libs::str::suffixarray sa(s);
  for (u32 i = 1; i < s.size(); ++i) std::cout << sa.sa[i] << " \n"[i + 1 == s.size()];
  return 0;
}

/*
读入一个长度为 $n$ 的由大小写英文字母或数字组成的字符串, 请把这个字符串的所有非空后缀按字典序 (用 ASCII 数值比较) 从小到大排序, 然后按顺序输出后缀的第一个字符在原串中的位置. 位置编号为 $1$ 到 $n$

## 输入
一行一个长度为 $n$ 的仅包含大小写英文字母或数字的字符串

## 输出
一行, 共 $n$ 个整数, 表示答案
*/

/*
ababa
=============
5 3 1 4 2
*/
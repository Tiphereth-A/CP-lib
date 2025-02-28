#define PROBLEM "https://www.luogu.com.cn/problem/P5788"

#include "../../code/ds/mono_stack.hpp"

vecu a;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu ans(n);
  a.resize(n);
  for (auto& i : a) std::cin >> i;
  auto f = [](u32 l, u32 r) { return a[l] >= a[r]; };
  tifa_libs::ds::mono_stack<u32, decltype(f)> stk;
  for (u32 i = n - 1; ~i; --i) {
    stk.pop_greater(i);
    ans[i] = stk.size() ? stk.top() + 1 : 0;
    stk.push_nocheck(i);
  }
  for (auto i : ans) std::cout << i << ' ';
}

/*
给出项数为 $n$ 的整数数列 $a_{1 \dots n}$
定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**, 即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$. 若不存在, 则 $f(i)=0$
试求出 $f(1\dots n)$

## 输入
第一行一个正整数 $n$
第二行 $n$ 个正整数 $a_{1\dots n}$
$1 \le n\leq 3\times 10^6$, $1\leq a_i\leq 10^9$

## 输出
一行 $n$ 个整数表示 $f(1), f(2), \dots, f(n)$ 的值
*/

/*
5
1 4 2 3 5
=============
2 5 4 5 0
*/
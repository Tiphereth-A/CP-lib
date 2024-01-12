#define PROBLEM "https://www.luogu.com.cn/problem/P5282"

#include "../../code/math/fact_mint.hpp"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_d31.hpp"
#include "../../code/poly/polydata_d.hpp"

using mintdata = tifa_libs::math::mintdata_d31<-1>;
using mint = tifa_libs::math::mint<mintdata>;
using polyd = tifa_libs::math::polydata_d<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n, p;
    std::cin >> n >> p;
    mintdata::set_mod(p);
    std::cout << tifa_libs::math::fact_mint<polyd>(n) << '\n';
  }
  return 0;
}

/*
给你正整数 $n$, 和一个质数 $p$, 你需要求出:
$$ n! \text{ mod } p$$
有 $T$ 组数据

## 输入格式

第一行一个正整数 $T$, 表示数据组数
接下来 $T$  行, 每行两个正整数 $n,p$, 意义如题目描述

## 输出格式

输出 $T$ 行, 表示每组数据的答案

## 数据范围

对于 $10\%$ 的数据: $p = 998244353$
对于另外 $10\%$ 的数据: $p = 1004535809$
对于 $100\%$ 的数据: $1\le n < p \le 2^{31}-1$, $1 \le T \le 5$
保证 $p$ 为质数
*/

/*
4
16777216 998244353
72267859 998244353
2333333 19260817
1919810 2147481811
=====================
789885751
569626621
16351109
1416439247
*/
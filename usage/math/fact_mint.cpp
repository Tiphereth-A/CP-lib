#define PROBLEM "https://www.luogu.com.cn/problem/P5282"

#include "../../include/math/fact_mint.hpp"

#include "../../include/math/mint.hpp"
#include "../../include/math/mint_d31.hpp"
#include "../../include/poly/polymtt.hpp"

using namespace tifa_libs;
using mint = math::mint<math::mint_d31, __LINE__>;
using poly = math::polymtt<mint>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 t;
  std::cin >> t;
  while (t--) {
    u32 n, p;
    std::cin >> n >> p;
    mint::set_mod(p);
    std::cout << math::fact_mint<poly>(n) << '\n';
  }
}

/*
给你正整数 $n$, 和一个质数 $p$, 你需要求出: $n! \text{ mod } p$
有 $T$ 组数据

## 输入
第一行一个正整数 $T$, 表示数据组数
接下来 $T$  行, 每行两个正整数 $n,p$, 意义如题目描述
$1\le n < p \le 2^{31}-1$, $1 \le T \le 5$, 保证 $p$ 为质数

## 输出
输出 $T$ 行, 表示每组数据的答案
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
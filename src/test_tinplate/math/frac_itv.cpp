#define PROBLEM "https://acm.hdu.edu.cn/showproblem.php?pid=6624"

#include "../../code/math/frac_itv.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  while (t--) {
    u64 p, x;
    std::cin >> p >> x;
    auto res = tifa_libs::math::frac_itv(tifa_libs::math::rational{x - 1, p}, tifa_libs::math::rational{x, p});
    std::cout << (res.den * x) % p << '/' << res.den << '\n';
  }
  return 0;
}

/*
给你两个正整数 $p$ 和 $x$, 其中 $p$ 是一个质数
请找到最小的正整数 $b$, 使得存在一些正整数 $a$ 满足 $a<b$ 且 $a\equiv bx\pmod p$

## 输入

第一行包含一个整数 $T$, 表示有 $T$ 个测试. 每个测试由一行组成, 包含两个整数 $p$ 和 $x$
$1\leq T\leq 2\times 10^5$, $3\leq p\leq 10^{15}$, $p$ 是质数, $1<x<p$

## 输出

对于每个测试, 输出一行包含一个字符串, 表示分数 $\frac{a}{b}$, 使用格式 "a/b"（不含引号）
*/

/*
3
11 7
998244353 554580197
998244353 998244352
============================
2/5
8/9
499122176/499122177
*/
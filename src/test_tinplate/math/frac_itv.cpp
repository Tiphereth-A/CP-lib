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
Many problems require printing the probability of something. Moreover, it is common that if the answer is $\frac{a}{b}$, you should output $a\times b^{-1}\pmod p$ ($p$ is a prime number). In these problems, you cannot know the exact value of the probability. It's so confusing!!! Now, we want to reverse engineer the exact probability from such calculated output value $x$. We do so by guessing the probability is the one with the minimum $b$ such that $a\times b^{-1}\equiv x\pmod p$. Now we invite you to solve this problem with us!

You are given two positive integers $p$ and $x$, where $p$ is a prime number.

Please find the smallest positive integer $b$ such that there exist some positive integer $a$ satisfying $a<b$ and $a\equiv bx\pmod p$.

**Input**

The first line contains an integer $T$ indicating there are $T$ tests. Each test consists of a single line containing two integers: $p,x$.

* $1\leq T\leq 2\times 10^5$

* $3\leq p\leq 10^{15}$

* $p$ is a prime

* $1<x<p$

**Output**

For each test, output a line containing a string represents the fraction $\frac{a}{b}$ using the format "a/b" (without quotes).
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
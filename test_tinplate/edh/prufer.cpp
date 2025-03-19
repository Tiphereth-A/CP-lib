#define PROBLEM "https://www.luogu.com.cn/problem/P6086"

#include "../../include/edh/prufer.hpp"

#include "../../include/edh/prufer_inv.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  u64 ans = 0;
  if (m == 1) {
    vecu a(n);
    flt_ (u32, i, 1, n) std::cin >> a[i];
    auto f = tifa_libs::prufer(a);
    for (u64 i = 1; i < n - 1; ++i) ans ^= i * f[i];
  } else {
    vecu a(n - 1);
    for (u32 i = 1; i < n - 1; ++i) std::cin >> a[i];
    auto f = tifa_libs::prufer_inv(a);
    flt_ (u64, i, 1, n) ans ^= i * f[i];
  }
  std::cout << ans << '\n';
}

/*
请实现 Prüfer 序列和无根树的相互转化
为方便你实现代码, 尽管是无根树, 我们在读入时仍将 $n$ 设为其根
对于一棵无根树, 设 $f_{1\dots n-1}$ 为其父亲序列 ($f_i$ 表示 $i$ 在 $n$ 为根时的父亲) , 设 $p_{1 \dots n-2}$ 为其 Prüfer 序列
另外, 对于一个长度为 $m$ 的序列 $a_{1 \dots m}$, 我们设其权值为 $\operatorname{xor}_{i = 1}^m i \times a_i$

## 输入
第一行两个整数 $n,m$, 表示树的点数和转化类型
若 $m = 1$, 第二行一行 $n-1$ 个整数, 表示父亲序列
若 $m = 2$, 第二行一行 $n-2$ 个整数, 表示 Prufer 序列

## 输出
若 $m = 1$, 一行一个整数, 表示给出的父亲序列对应的 Prüfer 序列的权值
若 $m = 2$, 一行一个整数, 表示给出的 Prüfer 序列对应的父亲序列的权值
*/

/*
6 1
3 6 4 6 1
============
29
*/
// p = {6 1 3 4}

/*
6 2
4 6 5 2
============
4
*/
// f = {4 6 6 5 2}
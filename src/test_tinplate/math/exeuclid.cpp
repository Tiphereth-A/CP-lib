#define PROBLEM "https://www.luogu.com.cn/problem/P5170"

#include "../../code/math/exeuclid.hpp"

#include "../../code/math/mint.hpp"
#include "../../code/math/mintdata_ss.hpp"

template <class T>
struct exeuclid_node {
  T u, r;
  T i, f, sqr_f, i_f;
  exeuclid_node(T u = 0, T r = 0, T i = 0, T f = 0, T sqr_f = 0, T i_f = 0) : u(u), r(r), i(i), f(f), sqr_f(sqr_f), i_f(i_f) {}
  friend exeuclid_node operator*(exeuclid_node const &l, exeuclid_node const &r) {
    return {l.u + r.u,
            l.r + r.r,
            l.i + r.i + l.r * r.r,
            l.f + r.f + l.u * r.r,
            l.sqr_f + r.sqr_f + l.u * l.u * r.r + 2 * l.u * r.f,
            l.i_f + r.i_f + l.u * l.r * r.r + l.u * r.i + l.r * r.f};
  }
};

using mintdata = tifa_libs::math::mintdata_ss<998244353>;
using mint = tifa_libs::math::mint<mintdata>;
using node = exeuclid_node<mint>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 t;
  std::cin >> t;
  node u(1, 0, 0, 0, 0, 0), r(0, 1, 1, 0, 0, 0);
  while (t--) {
    u64 n, a, b, c;
    std::cin >> n >> a >> b >> c;
    auto ans = tifa_libs::math::exeuclid(a, c, b, n, u, r);
    std::cout << (ans.f + b / c) << ' ' << (ans.sqr_f + (b / c) * (b / c)) << ' ' << ans.i_f << '\n';
  }
  return 0;
}

/*
给定 $n,\,a,\,b,\,c$ , 分别求 $\sum\limits_{i=0}^{n}\lfloor \frac{ai+b}{c} \rfloor\,,\  \sum\limits_{i=0}^{n}{\lfloor \frac{ai+b}{c} \rfloor}^2\,,\  \sum\limits_{i=0}^{n}i\lfloor \frac{ai+b}{c} \rfloor$ , 答案对 $998244353$ 取模. 多组数据

## 输入格式

第一行给出数据组数 $t$

接下来 $t$ 行, 每行有四个整数, 分别为每组数据的 $n,\ a,\ b,\ c$

## 输出格式

对于每组数据, 输出一行三个整数, 为三个答案对 $998244353$ 取模的结果
*/

/*
2
2 1 0 2
4 3 9 6
===========
1 1 2
11 27 27
*/
#define PROBLEM "https://www.luogu.com.cn/problem/P5807"

#include "../../code/graph/kirchhoff.hpp"

#include "../../code/graph/euler_trail.hpp"
#include "../../code/lalg/ge_euclid_mat.hpp"
#include "../../code/math/mint_s30.hpp"

using mint = tifa_libs::math::mint_s30<1'000'003>;

int main() {
  vec<mint> fact(200'005);
  fact[0] = 1;
  flt_ (u32, i, 1, (u32)fact.size()) fact[i] = fact[i - 1] * i;
  u32 T;
  std::cin >> T;
  while (T--) {
    u32 n;
    std::cin >> n;
    tifa_libs::graph::alist<true> g(n);
    for (u32 i = 0, s; i < n; ++i) {
      std::cin >> s;
      for (u32 j = 0, x; j < s; ++j) (std::cin >> x), g.add_arc(i, x - 1);
    }
    if (!tifa_libs::graph::is_eulerian(g)) {
      std::cout << "0\n";
      continue;
    }
    vecb vis(n);
    auto f = [&](auto &&f, u32 x) -> void {
      for (auto v : g.g[x])
        if (!vis[v]) vis[v] = 1, f(f, v);
    };
    vis[0] = 1, f(f, 0);
    vecu ids(n, -1_u32), inv_ids;
    u32 cnt_ids = 0;
    flt_ (u32, i, 0, n)
      if (vis[i]) ids[i] = cnt_ids++, inv_ids.push_back(i);
    tifa_libs::graph::amat<mint> mat(cnt_ids);
    flt_ (u32, id, 0, cnt_ids) {
      auto &tos = g.g[inv_ids[id]];
      if (tos.empty()) continue;
      std::ranges::sort(tos);
      u32 cnt = 1, pre = tos[0];
      flt_ (u32, j, 1, (u32)tos.size())
        if (tos[j] != pre) {
          mat.set_arc(id, ids[pre], cnt), pre = tos[j], cnt = 1;
        } else ++cnt;
      mat.set_arc(id, ids[pre], cnt);
    }
    auto is_0 = [](cT_(mint) x) { return x.val() == 0; };
    auto div = [](cT_(mint) x, cT_(mint) y) -> mint { return x.val() / y.val(); };
    auto ge = [&](tifa_libs::math::matrix<mint> &A, bool clear_u) { return tifa_libs::math::ge_euclid(A, is_0, div, clear_u); };
    mint ans = tifa_libs::graph::kirchhoff<true>(mat, ids[0], ge) * fact[g.deg_out[inv_ids[0]]];
    flt_ (u32, i, 1, cnt_ids) ans *= fact[g.deg_out[inv_ids[i]] - 1];
    std::cout << ans << '\n';
  }
  return 0;
}

/*
有 $n$ 个房间, 每个房间有若干把钥匙能够打开特定房间的门
最初你在房间 $1$. 每当你到达一个房间, 你可以选择该房间的一把钥匙, 前往该钥匙对应的房间, 并将该钥匙丢到垃圾桶中
你希望最终回到房间 $1$, 且垃圾桶中有所有的钥匙
你需要求出方案数, 答案对 $10^6 + 3$ 取模. 两组方案不同, 当且仅当使用钥匙的顺序不同
注意, 每把钥匙都是不同的

## 输入格式
多组数据, 第一行一个整数 $T$, 表示数据组数. 对于每组数据: 第一行一个整数 $n$. 接下来 $n$ 行, 第 $i$ 行描述房间 $i$: 首先一个数 $s$, 表示这个房间的钥匙数目, 接下来 $s$ 个数, 分别描述每把钥匙能够打开的房间的门
$1 \le T \le 15$, $1 \le n \le 100$, $0 \le \sum s \le 2 \times 10^5$

## 输出格式
对于每组数据, 一行一个整数, 表示答案对 $10^6+3$ 取模后的值

【样例说明】
在第一组样例中, 没有钥匙, 则方案数为 $1$
在第二组样例中, 你不可能使用第二个房间的钥匙, 所以方案数为 $0$
*/

/*
2
1
0
2
1 1
1 2
========
1
0
*/
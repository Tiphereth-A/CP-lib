#define PROBLEM "https://www.luogu.com.cn/problem/P4929"

#include "../../code/util/garsia_wachs.hpp"

void solve() {
  u32 n;
  std::cin >> n;
  vecu v(n + 2);
  flt_ (u32, i, 1, n + 1) std::cin >> v[i];
  v[0] = v[n + 1] = 0x3f3f3f3f;
  u32 ans = 0;
  tifa_libs::garsia_wachs(v, [&](u32, u32, u32, u32, u32 a) { ans += a; });
  std::cout << ans << '\n';
}

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  solve();
}

/*
在一个操场上摆放着一排 $N$ 堆石子. 现要将石子有次序地合并成一堆. 规定每次只能选相邻的 $2$ 堆石子合并成新的一堆, 并将新的一堆石子数记为该次合并的得分. 试设计一个算法, 计算出将 $N$ 堆石子合并成一堆的最小得分

## 输入
第一行一个整数 $N$. 接下来 $N$ 行, 第 $i$ 行一个整数 $a_i$, 代表第 $i$ 堆石子的石子数
$N \leq 40000, a_i \leq 200$

## 输出
输出将所有石子合并为一堆的最小得分
*/

/*
4
1
1
1
1
==========
8
*/

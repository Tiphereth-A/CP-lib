#define PROBLEM "https://www.luogu.com.cn/problem/P3386"

#include "../../include/graph/hopkap.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 l, r, m;
  std::cin >> l >> r >> m;
  vecptu edges(m);
  ++l, ++r;
  for (auto& [u, v] : edges) std::cin >> u >> v;
  auto ans = tifa_libs::graph::hopkap(l, r, edges);
  std::cout << ans.size() << '\n';
}

/*
给定一个二分图, 其左部点的个数为 $n$, 右部点的个数为 $m$, 边数为 $e$, 求其最大匹配的边数
左部点从 $1$ 至 $n$ 编号, 右部点从 $1$ 至 $m$ 编号

## 输入格式
输入的第一行是三个整数, 分别代表 $n$, $m$ 和 $e$
接下来 $e$ 行, 每行两个整数 $u, v$, 表示存在一条连接左部点 $u$ 和右部点 $v$ 的边
- $1 \leq n, m \leq 500$
- $1 \leq e \leq 5 \times 10^4$
- $1 \leq u \leq n$, $1 \leq v \leq m$
不保证给出的图没有重边

## 输出格式
输出一行一个整数, 代表二分图最大匹配的边数
*/

/*
1 1 1
1 1
========
1
*/

/*
4 2 7
3 1
1 2
3 2
1 1
4 2
4 1
1 1
=======
2
*/
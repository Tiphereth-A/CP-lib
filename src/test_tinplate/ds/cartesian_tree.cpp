#define PROBLEM "https://www.luogu.com.cn/problem/P5854"

#include "../../code/ds/cartesian_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<i32> a(n);
  for (auto &x : a) std::cin >> x;
  tifa_libs::ds::cartesian_tree tr(a);
  i64 retl = 0, retr = 0;
  flt_ (u32, i, 0, n) {
    retl ^= 1ll * (i + 1) * (~tr.t[i].son[0] ? tr.t[i].son[0] + 2 : 1);
    retr ^= 1ll * (i + 1) * (~tr.t[i].son[1] ? tr.t[i].son[1] + 2 : 1);
  }
  std::cout << retl << ' ' << retr << '\n';
  return 0;
}

/*
给定一个 $1 \sim n$ 的排列 $p$, 构建其笛卡尔树, 即构建一棵二叉树, 满足:
1. 每个节点的编号满足二叉搜索树的性质
2. 节点 $i$ 的权值为 $p_i$, 每个节点的权值满足小根堆的性质

## 输入

第一行一个整数 $n$
第二行一个排列 $p_{1 \dots n}$
$1 \le n \le 10^7$

## 输出

设 $l_i,r_i$ 分别表示节点 $i$ 的左右儿子的编号 (若不存在则为 $0$)
一行两个整数, 分别表示 $\operatorname{xor}_{i = 1}^n i \times (l_i + 1)$ 和 $\operatorname{xor}_{i = 1}^n i \times (r_i + 1)$

样例解释

| i | l_i | r_i |
| - | --- | --- |
| 1 | 0   | 0   |
| 2 | 1   | 4   |
| 3 | 0   | 0   |
| 4 | 3   | 5   |
| 5 | 0   | 0   |
*/

/*
5
4 1 3 2 5
===========
19 21
*/
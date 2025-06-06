#define PROBLEM "https://www.luogu.com.cn/problem/P3381"

#include "../../include/graph/ssp.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, s, t;
  std::cin >> n >> m >> s >> t, --s, --t;
  graph::ssp mcmf(n, s, t);
  i32 c;
  for (u32 i = 0, u, v, w; i < m; ++i) std::cin >> u >> v >> w >> c, --u, --v, mcmf.add(u, v, w, c);
  auto [flow, cost] = mcmf.get();
  std::cout << flow << ' ' << cost;
}

/*
给出一个包含 $n$ 个点和 $m$ 条边的有向图 (下面称其为网络)  $G=(V,E)$, 该网络上所有点分别编号为 $1 \sim n$, 所有边分别编号为 $1\sim m$, 其中该网络的源点为 $s$, 汇点为 $t$, 网络上的每条边 $(u,v)$ 都有一个流量限制 $w(u,v)$ 和单位流量的费用 $c(u,v)$
你需要给每条边 $(u,v)$ 确定一个流量 $f(u,v)$, 要求:
1.  $0 \leq f(u,v) \leq w(u,v)$ (每条边的流量不超过其流量限制) ;
2. $\forall p \in \{V \setminus \{s,t\}\}$, $\sum_{(i,p) \in E}f(i,p)=\sum_{(p,i)\in E}f(p,i)$ (除了源点和汇点外, 其他各点流入的流量和流出的流量相等);
3. $\sum_{(s,i)\in E}f(s,i)=\sum_{(i,t)\in E}f(i,t)$ (源点流出的流量等于汇点流入的流量)
定义网络 $G$ 的流量 $F(G)=\sum_{(s,i)\in E}f(s,i)$, 网络 $G$ 的费用 $C(G)=\sum_{(i,j)\in E} f(i,j) \times c(i,j)$
你需要求出该网络的最小费用最大流, 即在 $F(G)$ 最大的前提下, 使 $C(G)$ 最小

## 输入
输入第一行包含四个整数 $n,m,s,t$, 分别代表该网络的点数 $n$, 网络的边数 $m$, 源点编号 $s$, 汇点编号 $t$
接下来 $m$ 行, 每行四个整数 $u_i,v_i,w_i,c_i$, 分别代表第 $i$ 条边的起点, 终点, 流量限制, 单位流量费用
$1 \leq n \leq 5\times 10^3$, $1 \leq m \leq 5 \times 10^4$, $1 \leq s,t \leq n$, $u_i \neq v_i$, $0 \leq w_i,c_i \leq 10^3$, 且该网络的最大流和最小费用 $\leq 2^{31}-1$
输入数据随机生成

## 输出
输出两个整数, 分别为该网络的最大流 $F(G)$, 以及在 $F(G)$ 最大的前提下, 该网络的最小费用 $C(G)$
*/

/*
4 5 4 3
4 2 30 2
4 3 20 3
2 3 20 1
2 1 30 9
1 3 40 5
===========
50 280
*/
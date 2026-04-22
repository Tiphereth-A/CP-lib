// competitive-verifier: DISPLAY never
// cplib.manager: PROBLEM https://www.luogu.com.cn/problem/P11175

#include "lib.hpp"
using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  u64 P;
  u32 g;
  std::cin >> P >> g;
  bsgs_fix solver;
  solver.init(g, P);
  u32 q;
  std::cin >> q;
  while (q--) {
    u64 y;
    std::cin >> y;
    std::cout << solver(y) << '\n';
  }
}

/*
给定质数 $P$ 以及它的一个原根 $g$. 有 $q$ 组询问, 每组询问给出整数 $y$, 你需要找到最小的非负整数 $x$ 使得 $g^x\equiv y\pmod P$.

## 输入
第一行两个整数 $P,g$, 描述质数 $P$ 及其一个原根 $g$. 第二行一个整数 $q$, 表示询问次数. 接下来 $q$ 行, 每行一个整数 $y$, 表示每次询问的值.
$1\le g,y_i<P\le 10^9+7$, $1\le q\le 5\times 10^5$.

## 输出
输出共 $q$ 行, 每行一个整数表示答案.
*/

/*sample
998244353 3
9
1
11
111
1111
11111
111111
1111111
11111111
111111111
============
0
258630203
771331691
346105458
268271589
571255383
916731589
304666893
915484870
*/

/*sample
1000000007 5
13
1
5
25
125
625
3125
15625
78125
390625
1953125
9765625
48828125
244140625
============
0
1
2
3
4
5
6
7
8
9
10
11
12
*/

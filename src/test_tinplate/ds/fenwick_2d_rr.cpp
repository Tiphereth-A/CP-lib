#define PROBLEM "https://www.luogu.com.cn/problem/P3372"

#include "../../code/ds/fenwick_2d_rr.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m;
  std::cin.get();
  std::cin >> n >> m;
  tifa_libs::ds::fenwick2d_rr<i32> tr(n + 1, m + 1);
  char op;
  for (i32 l1, r1, l2, r2, d; std::cin >> op >> l1 >> r1 >> l2 >> r2;) {
    if (op == 'L') {
      std::cin >> d;
      tr.add(l1, r1, l2 + 1, r2 + 1, d);
    } else std::cout << tr.sum(l1 - 1, r1 - 1, l2, r2) << '\n';
  }
  return 0;
}

/*
## 输入格式

输入数据的第一行为 `X n m`, 代表矩阵大小为 $n\times m$
从输入数据的第二行开始到文件尾的每一行会出现以下两种操作:
-    `L a b c d delta` —— 代表将 $(a,b),(c,d)$ 为顶点的矩形区域内的所有数字加上 $delta$
-    `k a b c d`     —— 代表求 $(a,b),(c,d)$ 为顶点的矩形区域内所有数字的和

请注意, $k$ 为小写

## 输出格式

针对每个 $k$ 操作, 在单独的一行输出答案

## 提示

对于 $10\%$ 的数据, $1 \le n \le 16$, $1 \le m \le 16$,  操作不超过 $200$ 个

对于 $60\%$ 的数据, $1 \le n \le 512$, $1 \le m \le 512$

对于 $100\%$ 的数据, $1 \le n \le 2048$, $1 \le m \le 2048$, $-500 \le delta \le 500$, 操作不超过 $2\times 10^5$ 个, 保证运算过程中及最终结果均不超过 $32$ 位带符号整数类型的表示范围
*/

/*
X 4 4
L 1 1 3 3 2
L 2 2 4 4 1
k 2 2 3 3
==========
12
*/
#define PROBLEM "https://www.luogu.com.cn/problem/P3372"

#include "../../include/ds/fenwick_2d_rr.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin.get(), std::cin >> n >> m;
  tifa_libs::ds::fenwick2d_rr<i32> tr(n + 1, m + 1);
  char op;
  for (i32 l1, r1, l2, r2, d; std::cin >> op >> l1 >> r1 >> l2 >> r2;) {
    if (op == 'L') std::cin >> d, tr.add(l1, r1, l2 + 1, r2 + 1, d);
    else std::cout << tr.sum(l1 - 1, r1 - 1, l2, r2) << '\n';
  }
}

/*
## 输入
第一行为 `X n m`, 代表矩阵大小为 $n\times m$. 从第二行开始到文件尾的每一行会出现以下两种操作:
- `L a b c d delta` 代表将 $(a,b),(c,d)$ 为顶点的矩形区域内的所有数字加上 $delta$
- `k a b c d`       代表求 $(a,b),(c,d)$ 为顶点的矩形区域内所有数字的和
$1 \le n \le 2048$, $1 \le m \le 2048$, $-500 \le delta \le 500$, 操作不超过 $2\times 10^5$ 个, 保证运算过程中及最终结果均不超过 $32$ 位带符号整数类型的表示范围

## 输出
针对每个 `k` 操作, 在单独的一行输出答案
*/

/*
X 4 4
L 1 1 3 3 2
L 2 2 4 4 1
k 2 2 3 3
==========
12
*/
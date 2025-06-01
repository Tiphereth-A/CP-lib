#define PROBLEM "https://www.luogu.com.cn/problem/P4148"

#include "../../include/ds/kdtree.hpp"

using namespace tifa_libs;
int op(int x, int y) { return x + y; }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  ds::KDtree<int, op> kdt(1897);
  using point_t = decltype(kdt)::point;
  u32 n;
  std::cin >> n;
  int ans = 0;
  point_t p1, p2;
  while (true) {
    u32 opt;
    std::cin >> opt;
    if (opt == 1) {
      int A;
      std::cin >> p1[0] >> p1[1] >> A;
      p1[0] ^= ans, p1[1] ^= ans, A ^= ans;
      kdt.insert(p1, A);
    } else if (opt == 2) {
      std::cin >> p1[0] >> p1[1] >> p2[0] >> p2[1];
      p1[0] ^= ans, p1[1] ^= ans, p2[0] ^= ans, p2[1] ^= ans;
      std::cout << (ans = kdt.query(p1, p2)) << '\n';
    } else return 0;
  }
}

/*
你有一个$N \times N$的棋盘, 每个格子内有一个整数, 初始时的时候全部为 $0$, 现在需要维护两种操作：
- `1 x y A`    $1\le x,y\le N$, $A$ 是正整数. 将格子`x`,`y`里的数字加上 $A$
- `2 x1 y1 x2 y2`    $1 \le x_1 \le x_2 \le N$, $1 \le y_1\le y_2 \le N$. 输出 $x_1, y_1, x_2, y_2$ 这个矩形内的数字和
- `3`    无 终止程序

## 输入
输入文件第一行一个正整数 $N$
接下来每行一个操作. 每条命令除第一个数字之外, 均要异或上一次输出的答案 `last_ans`, 初始时 `last_ans` $=0$
$1\leq N\leq 5\times 10^5$, 操作数不超过 $2\times 10^5$ 个, 内存限制 $20\texttt{MB}$, 保证答案在 int 范围内并且解码之后数据仍合法

## 输出
对于每个 $2$ 操作, 输出一个对应的答案
*/

/*
4
1 2 3 3
2 1 1 3 3
1 1 1 1
2 1 1 0 7
3
==============
3
5
*/
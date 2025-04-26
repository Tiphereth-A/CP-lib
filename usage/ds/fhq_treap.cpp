#define PROBLEM "https://www.luogu.com.cn/problem/P3369"

#include "../../include/ds/fhq_treap.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  tifa_libs::ds::fhq_treap<i32> treap;
  for (u32 i = 0, opt; i < n; ++i) {
    i32 x;
    std::cin >> opt >> x;
    if (opt == 1) treap.insert(x);
    else if (opt == 2) treap.erase(x);
    else if (opt == 3) std::cout << treap.rank(x) << '\n';
    else if (opt == 4) std::cout << treap.kth((u32)x).value() << '\n';
    else if (opt == 5) std::cout << treap.prev(x).value() << '\n';
    else std::cout << treap.next(x).value() << '\n';
  }
}

/*
您需要写一种数据结构来维护一些数, 其中需要提供以下操作:
1. 插入 $x$ 数
2. 删除 $x$ 数(若有多个相同的数, 应只删除一个)
3. 查询 $x$ 数的排名(排名定义为比当前数小的数的个数 $+1$)
4. 查询排名为 $x$ 的数
5. 求 $x$ 的前驱(前驱定义为小于 $x$, 且最大的数)
6. 求 $x$ 的后继(后继定义为大于 $x$, 且最小的数)

## 输入
第一行为 $n$, 表示操作的个数,下面 $n$ 行每行有两个数 $\text{opt}$ 和 $x$, $\text{opt}$ 表示操作的序号( $ 1 \leq \text{opt} \leq 6 $ )

## 输出
对于操作 $3,4,5,6$ 每行输出一个数, 表示对应答案
*/

/*
10
1 106465
4 1
1 317721
1 460929
1 644985
1 84185
1 89851
6 81968
1 492737
5 493598
===========
106465
84185
492737
*/
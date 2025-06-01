#define PROBLEM "https://www.luogu.com.cn/problem/P4979"

#include "../../include/ds/odt.hpp"

using namespace tifa_libs;
const strn YN_[2] = {"No", "Yes"};

int main() {
  u32 n, m;
  strn s;
  std::cin >> n >> s >> m;
  ds::ODT<char> odt;
  for (u32 l = 0, r = 0; l < n; l = r) {
    while (r < n && s[++r] == s[l]);
    odt.insert(l + 1, r, s[l]);
  }
  flt_ (u32, i, 0, m) {
    char op, c;
    u32 l, r;
    std::cin >> op >> l >> r;
    switch (op) {
      case 'A':
        std::cin >> c;
        odt.assign_merge(l, r, c);
        break;
      case 'B':
        std::cout << YN_[odt.run_no_split(l, r, [&](auto itl, auto itr) {
          if (itl != itr) return false;
          if (!(l != 1 && r != n)) return true;
          if (l > itl->l && r < itl->r) return false;
          if (l == itl->l && r != itl->r) return std::prev(itl)->v != itl->v;
          if (l != itl->l && r == itl->r) return std::next(itl)->v != itl->v;
          return std::prev(itl)->v != std::next(itl)->v;
        })] << '\n';
    }
  }
}

/*
CYJian 家的矿共出产 $A,B,C$ 三种矿石, 所以我们也只能用 $A,B,C$ 三种材料来修复他们家的矿. 我们已知共有 $N$ 吨材料, 每吨材料均为 $A,B,C$ 三种材料中的一种, 它们连成了一个串, 如 $ABCBCABCBACBCBAA$
CYJian 家对材料的要求非常严格, 他每次会选择一段连续区间的材料作为修复的材料. 因为不合要求的材料会使得矿再次塌陷, 砸死 CYJian, 所以这个连续区间的材料必须满足一下 $2$ 个要求:
- 这段连续区间必须是同一种材料
- 这段连续区间的前一个材料与后一个材料必须不相同.
例如, 有一段材料为 $AACBBABBBCCCBBB$, 则 $(4$~$5)$ 区间的 $BB$ 和 $(5$~$5)$ 区间的 $B$ 均符合要求, 而 $(10$~$12)$ 区间的 $CCC$ 不符合要求.
材料有灵性, 所以材料会有变化.
现在有 $N$ 吨材料, $K$ 个询问. 每个询问是以下的 $2$ 种形式之一:
- `A x y op` 表示替换材料, 将 $x$ 到 $y(1\leq x\leq y\leq N)$ 区间内的材料替换为 $op$, $op$ 为 $A,B,C$ 三种材料字符中的一个.
- `B x y` 表示是否询问, 即询问 $x$ 到 $y(1\leq x\leq y\leq N)$ 区间内的材料是否合法, 合法输出 `Yes`, 不合法输出 `No`.
注意: 当 $x=1$ 或$y=N$ 时, 你的程序不需要判断前后的情况, 而只需要判断区间内的情况.

## 输入
第一行一个正整数 $N$
接下来 $N$ 个字符, 表示材料
接下来 $K$ 个询问, 格式为上述的一种
$N\le500000,K\le500000,1<x\le y<N$

## 输出
对于每个 `B x y` 的询问, 输出 `Yes` 或 `No`
*/

/*
15
AACBBABBBCCCBBB
3
B 4 5
B 5 5
B 10 12
=====================
Yes
Yes
No
*/

/*
5
ABBBB
2
B 1 4
B 2 5
==========
No
Yes
*/
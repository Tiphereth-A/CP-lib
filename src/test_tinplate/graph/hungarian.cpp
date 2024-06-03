#define PROBLEM "https://www.luogu.com.cn/problem/P4014"

#include "../../code/graph/hungarian.hpp"

#include "../../code/io/ios_container.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vveci c1(n, veci(n));
  for (auto &i : c1) std::cin >> i;
  auto c2 = c1;
  for (auto &i : c2)
    for (auto &j : i) j = -j;
  std::cout << tifa_libs::graph::hungarian(c1).back() << '\n';
  std::cout << -tifa_libs::graph::hungarian(c2).back() << '\n';
}

/*
有 $n$ 件工作要分配给 $n$ 个人做. 第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{ij}$. 试设计一个将 $n$ 件工作分配给 $n$ 个人做的分配方案, 使产生的总效益最小或最大

## 输入格式
文件的第一行有 $1$ 个正整数 $n$, 表示有 $n$ 件工作要分配给 $n$ 个人做
接下来的 $n$ 行中, 每行有 $n$ 个整数 $c_{i,j}$, 表示第 $i$ 个人做第 $j$ 件工作产生的效益为 $c_{i,j}$

## 输出格式
两行分别输出最小总效益和最大总效益

## 提示
$1 \leq n \leq 50, 0 \le c _ {i, j} \le 100$
一个人只能修一个工件
*/

/*
5
2 2 2 1 2
2 3 1 2 4
2 0 1 1 1
2 3 4 3 3
3 2 1 2 1
=============
5
14
*/
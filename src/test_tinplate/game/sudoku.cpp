#define PROBLEM "https://www.luogu.com.cn/problem/P1784"

#include "../../code/game/sudoku.hpp"

void solve() {
  vvecu sdk(9, vecu(9));
  for (auto &i : sdk)
    for (auto &j : i) std::cin >> j;
  auto res = tifa_libs::game::sudoku_solver(sdk)[0];
  flt_ (u32, i, 0, 9)
    flt_ (u32, j, 0, 9) std::cout << res[i][j] << " \n"[j == 8];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}

/*
## 输入

一个未填的数独

## 输出

填好的数独
*/

/*
8 0 0 0 0 0 0 0 0
0 0 3 6 0 0 0 0 0
0 7 0 0 9 0 2 0 0
0 5 0 0 0 7 0 0 0
0 0 0 0 4 5 7 0 0
0 0 0 1 0 0 0 3 0
0 0 1 0 0 0 0 6 8
0 0 8 5 0 0 0 1 0
0 9 0 0 0 0 4 0 0
====================
8 1 2 7 5 3 6 4 9
9 4 3 6 8 2 1 7 5
6 7 5 4 9 1 2 8 3
1 5 4 2 3 7 8 9 6
3 6 9 8 4 5 7 2 1
2 8 7 1 6 9 5 3 4
5 2 1 9 7 4 3 6 8
4 3 8 5 2 6 9 1 7
7 9 6 3 1 8 4 5 2
*/

/*
9 0 0 8 0 0 0 0 0
0 0 0 0 0 0 5 0 0
0 0 0 0 0 0 0 0 0
0 2 0 0 1 0 0 0 3
0 1 0 0 0 0 0 6 0
0 0 0 4 0 0 0 7 0
7 0 8 6 0 0 0 0 0
0 0 0 0 3 0 1 0 0
4 0 0 0 0 0 2 0 0
=====================
9 7 2 8 5 3 6 1 4
1 4 6 2 7 9 5 3 8
5 8 3 1 4 6 7 2 9
6 2 4 7 1 8 9 5 3
8 1 7 3 9 5 4 6 2
3 5 9 4 6 2 8 7 1
7 9 8 6 2 1 3 4 5
2 6 5 9 3 4 1 8 7
4 3 1 5 8 7 2 9 6
*/
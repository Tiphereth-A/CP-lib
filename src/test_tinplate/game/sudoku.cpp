#define PROBLEM "https://www.luogu.com.cn/problem/P1784"

#include "../../code/game/sudoku.hpp"

void solve() {
  vvec<size_t> sdk(9, vec<size_t>(9));
  for (auto &i : sdk)
    for (auto &j : i) std::cin >> j;
  auto res = tifa_libs::game::sudoku_solver(sdk)[0];
  for (size_t i = 0; i < 9; ++i)
    for (size_t j = 0; j < 9; ++j) std::cout << res[i][j] << " \n"[j == 8];
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}
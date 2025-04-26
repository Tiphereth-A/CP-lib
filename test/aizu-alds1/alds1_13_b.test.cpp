#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_13_B"

#include "../../include/game/npuzzle_data.hpp"
#include "../../include/opt/astar.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  tifa_libs::game::NPuzzleData start(3);
  std::vector<u32> fin(9);
  std::iota(fin.begin(), fin.end() - 1, 1);
  tifa_libs::game::NPuzzleData::set_fin(3, fin);
  tifa_libs::game::NPuzzleData::limit = 100;
  std::cin >> start;
  std::cout << tifa_libs::opt::astar(start)->moves.size() << '\n';
  return 0;
}

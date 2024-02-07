#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_13_C"

#include "../../code/game/npuzzle_data.hpp"
#include "../../code/opt/astar.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::game::NPuzzleData start(4);
  std::cin >> start;
  for (auto& i : start.node())
    if (i) --i;
    else i = 15;
  std::cout << tifa_libs::opt::astar(start)->moves().size() << '\n';
  return 0;
}

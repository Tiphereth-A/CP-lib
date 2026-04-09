// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_13_B
#include "../../../src/game/npuzzle_data/lib.hpp"
#include "../../../src/opt/astar/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  npuzzle_data start(3);
  std::vector<u32> fin(9);
  std::iota(begin(fin), end(fin) - 1, 1);
  npuzzle_data::set_fin(3, fin);
  npuzzle_data::limit = 100;
  std::cin >> start;
  std::cout << astar(start)->moves.size() << '\n';
  return 0;
}

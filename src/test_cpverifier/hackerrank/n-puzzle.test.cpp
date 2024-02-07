#define PROBLEM "https://www.hackerrank.com/challenges/n-puzzle/problem"

#include "../../code/game/npuzzle_data.hpp"
#include "../../code/opt/astar.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  tifa_libs::game::NPuzzleData start(n);
  std::cin >> start;
  auto v = tifa_libs::opt::astar(start)->moves();
  std::cout << v.size() << '\n';
  for (auto i : v) switch (i) {
      case tifa_libs::game::U: std::cout << "UP\n"; break;
      case tifa_libs::game::D: std::cout << "DOWN\n"; break;
      case tifa_libs::game::L: std::cout << "LEFT\n"; break;
      case tifa_libs::game::R: std::cout << "RIGHT\n"; break;
    }
  return 0;
}

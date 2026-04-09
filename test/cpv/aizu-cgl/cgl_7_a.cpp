// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_7_A
#include "../../../src/geo2d/ds/c/lib.hpp"
#include "../../../src/geo2d/rel/cc/lib.hpp"

using namespace tifa_libs;
using circ = circle<double>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  circ c1, c2;
  std::cin >> c1 >> c2;
  switch (relation_CC(c1, c2)) {
    case RELCC::lyingin: std::cout << "0\n"; break;
    case RELCC::touchin: std::cout << "1\n"; break;
    case RELCC::intersect: std::cout << "2\n"; break;
    case RELCC::touchex: std::cout << "3\n"; break;
    case RELCC::lyingout: std::cout << "4\n"; break;
  }
  return 0;
}

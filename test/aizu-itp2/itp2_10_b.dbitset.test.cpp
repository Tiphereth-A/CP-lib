#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_B"

#include "../../include/ds/dbitset.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 a, b;
  std::cin >> a >> b;
  ds::dbitset ba(32), bb(32);
  ba.getword(0) = a;
  bb.getword(0) = b;
  std::cout << (ba & bb) << '\n';
  std::cout << (ba | bb) << '\n';
  std::cout << (ba ^ bb) << '\n';
  return 0;
}
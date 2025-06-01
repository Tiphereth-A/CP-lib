#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_10_A"

#include "../../include/ds/dbitset.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  ds::dbitset bs(32);
  bs.getword(0) = n;
  std::cout << bs << '\n';
  std::cout << ~bs << '\n';
  std::cout << (bs << 1).to_string().substr(1) << '\n';
  std::cout << '0' << (bs >> 1) << '\n';
  return 0;
}
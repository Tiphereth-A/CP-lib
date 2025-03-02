#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E"

#include "../../code/opt/lev_dis.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn a, b;
  std::cin >> a >> b;
  std::cout << tifa_libs::opt::lev_dis(a, b).back().back() << '\n';
  return 0;
}

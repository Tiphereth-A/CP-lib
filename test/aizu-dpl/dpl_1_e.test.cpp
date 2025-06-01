#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_E"

#include "../../include/opt/lev_dis.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  strn a, b;
  std::cin >> a >> b;
  std::cout << opt::lev_dis(a, b).back().back() << '\n';
  return 0;
}

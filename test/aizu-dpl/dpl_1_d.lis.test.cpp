#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_D"

#include "../../include/io/ios_container.hpp"
#include "../../include/opt/lis.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu v(n);
  std::cin >> v;
  std::cout << opt::lis(v).size() << '\n';
  return 0;
}

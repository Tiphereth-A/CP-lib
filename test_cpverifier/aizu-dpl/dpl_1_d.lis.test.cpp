#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_D"

#include "../../include/io/ios_container.hpp"
#include "../../include/opt/lis.hpp"

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu v(n);
  std::cin >> v;
  std::cout << tifa_libs::opt::lis(v).size() << '\n';
  return 0;
}

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_1_D"

#include "../../code/io/ios_container.hpp"
#include "../../code/opt/lis.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<u32> v(n);
  std::cin >> v;
  std::cout << tifa_libs::opt::lis(v).size() << '\n';
  return 0;
}

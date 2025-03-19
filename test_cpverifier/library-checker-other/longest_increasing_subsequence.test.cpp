#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include "../../include/io/ios_container.hpp"
#include "../../include/opt/lis.hpp"

CEXP u32 inf = 1145141919;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  auto res = tifa_libs::opt::lis(a, inf);
  std::cout << res.size() << '\n'
            << res << '\n';
  return 0;
}

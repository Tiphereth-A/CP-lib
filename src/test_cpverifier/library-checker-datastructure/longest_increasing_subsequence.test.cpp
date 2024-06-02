#define PROBLEM "https://judge.yosupo.jp/problem/longest_increasing_subsequence"

#include "../../code/io/ios_container.hpp"
#include "../../code/math/youngt.hpp"
#include "../../code/opt/lis.hpp"

CEXP u32 inf = 1145141919;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;
  vecu a(n);
  std::cin >> a;
  tifa_libs::math::Youngt yt(a);
  std::cout << yt.width() << '\n'
            << tifa_libs::opt::lis(a, inf) << '\n';
  return 0;
}

#define PROBLEM "https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary"

#include "../../../src/conv/min_plus/cv/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m;
  std::cin >> n >> m;
  vecu a(n), b(m);
  std::cin >> a >> b;
  std::cout << math::conv_minplus_cv(a, b) << '\n';
  return 0;
}

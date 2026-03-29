#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "../../../src/lalg/bmat/ge/lib.hpp"
#include "../../../src/lalg/ds/bmat/lib.hpp"

using namespace tifa_libs;
using mat = bitmat<1 << 24>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;

  mat bm(n, n);
  std::cin >> bm;
  auto rk = ge_bmat(bm, false);
  std::cout << (rk == n) << '\n';

  return 0;
}

#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../../src/lalg/bmat/mul/lib.hpp"
#include "../../../src/lalg/ds/bmat/lib.hpp"

using namespace tifa_libs;

using mat = bitmat<1 << 24>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;

  mat a(n, m), b(m, k);
  std::cin >> a;
  b.read_trans(std::cin, m, k);
  auto c = mul_bmat(a, b);
  std::cout << c << '\n';

  return 0;
}

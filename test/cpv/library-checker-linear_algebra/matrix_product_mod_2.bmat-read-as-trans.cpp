#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../../src/lalg/bmat/mul/lib.hpp"
#include "../../../src/lalg/ds/bmat/lib.hpp"

using namespace tifa_libs;
template <usz N>
using mat = bitmat<N>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;

#define DO(num)                           \
  if (std::max({n, m, k}) <= num) {       \
    mat<num> a, b;                        \
    read_bitmat(std::cin, a, n, m);       \
    read_bitmat_trans(std::cin, b, m, k); \
    auto c = mul_bmat(a, b);              \
    print_bitmat(std::cout, c, n, k);     \
    return 0;                             \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}

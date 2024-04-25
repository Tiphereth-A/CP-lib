#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../code/lalg/bitmat.hpp"
#include "../../code/lalg/mul_bmat.hpp"
#include "../../code/lalg/trans_bmat.hpp"

template <usz N>
using mat = tifa_libs::math::bitmat<N>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, m, k;
  std::cin >> n >> m >> k;

#define DO(num)                                                            \
  if (tifa_libs::max({n, m, k}) <= num) {                                  \
    mat<num> a, b;                                                         \
    tifa_libs::math::read_bitmat(std::cin, a, n, m);                       \
    tifa_libs::math::read_bitmat(std::cin, b, m, k);                       \
    auto c = tifa_libs::math::mul_bmat(a, tifa_libs::math::trans_bmat(b)); \
    tifa_libs::math::print_bitmat(std::cout, c, n, k);                     \
    return 0;                                                              \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}

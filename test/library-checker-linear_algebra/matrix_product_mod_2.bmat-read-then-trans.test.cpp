#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product_mod_2"

#include "../../include/lalg/bitmat.hpp"
#include "../../include/lalg/mul_bmat.hpp"
#include "../../include/lalg/trans_bmat.hpp"

using namespace tifa_libs;
template <usz N>
using mat = math::bitmat<N>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, m, k;
  std::cin >> n >> m >> k;

#define DO(num)                                      \
  if (std::max({n, m, k}) <= num) {                  \
    mat<num> a, b;                                   \
    math::read_bitmat(std::cin, a, n, m);            \
    math::read_bitmat(std::cin, b, m, k);            \
    auto c = math::mul_bmat(a, math::trans_bmat(b)); \
    math::print_bitmat(std::cout, c, n, k);          \
    return 0;                                        \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}

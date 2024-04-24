#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "../../code/lalg/bitmat.hpp"
#include "../../code/lalg/ge_bmat.hpp"

template <usz N>
using mat = tifa_libs::math::bitmat<N>;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;

#define DO(num)                                       \
  if (n <= num) {                                     \
    mat<num> bm;                                      \
    tifa_libs::math::read_bitmat(std::cin, bm, n, n); \
    auto rk = tifa_libs::math::ge_bmat(bm, false);    \
    std::cout << (rk == n) << '\n';                   \
    return 0;                                         \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}
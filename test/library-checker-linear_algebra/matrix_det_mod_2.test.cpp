#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "../../include/lalg/bitmat.hpp"
#include "../../include/lalg/ge_bmat.hpp"

using namespace tifa_libs;
template <usz N>
using mat = math::bitmat<N>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;

#define DO(num)                                       \
  if (n <= num) {                                     \
    mat<num> bm;                                      \
    math::read_bitmat(std::cin, bm, n, n); \
    auto rk = math::ge_bmat(bm, false);    \
    std::cout << (rk == n) << '\n';                   \
    return 0;                                         \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}

#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"

#include "../../../src/lalg/bmat/inv/lib.hpp"

using namespace tifa_libs;
template <usz N>
using mat = bitmat<N>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n;
  std::cin >> n;

#define DO(num)                                                \
  if (n <= num) {                                              \
    mat<num> bm;                                               \
    read_bitmat(std::cin, bm, n, n);                           \
    if (auto res = inv_bmat(bm, n); !res) std::cout << "-1\n"; \
    else print_bitmat(std::cout, res.value(), n, n);           \
    return 0;                                                  \
  }

  DO(1 << 6)
  DO(1 << 8)
  DO(1 << 12)

  return 0;
}

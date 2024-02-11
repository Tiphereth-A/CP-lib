#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_B"

#include "../../code/math/isqrt.hpp"
#include "../../code/util/blocking.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  tifa_libs::blocking<u32> blk(std::max(1_u32, tifa_libs::math::isqrt(n)), vec<u32>(n), [](u32& b, auto, auto) { b = 0; });
  for (u32 i = 0, op, x, y, res; i < q; ++i) {
    std::cin >> op >> x >> y;
    if (op) {
      res = 0;
      blk.run(
          x, y + 1,
          [&](u32, auto l, auto r) { res += std::reduce(l, r); },
          [&](u32 b, auto l, auto r) { res += b * (r - l); });
      std::cout << res << '\n';
    } else blk.run(
        x, x + 1,
        [&](u32& b, auto l, auto r) {
          b += y;
          for (auto i = l; i != r; ++i) *i += y;
        },
        [&](u32& b, auto, auto) { b += y; });
  }
  return 0;
}

#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_C"

#include "../../code/math/mint.hpp"
#include "../../code/math/mint_2e61n1.hpp"
#include "../../code/str/hash_substr_2d.hpp"

using mint = tifa_libs::math::mint<tifa_libs::math::mint_2e61n1>;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 h, w;
  std::cin >> h >> w;
  vec<strn> a(h);
  for (auto& i : a) std::cin >> i;
  u32 r, c;
  std::cin >> r >> c;
  vec<strn> b(r);
  for (auto& i : b) std::cin >> i;
  if (h < r || w < c) return 0;
  tifa_libs::str::hash_substr_2d<mint> ha, hb;
  ha.set(a, c);
  hb.set(b, c);
  flt_ (u32, i, 0, h - r + 1)
    flt_ (u32, j, 0, w - c + 1)
      if (ha.get(i, j, r) == hb.get(0, 0, r)) std::cout << i << " " << j << '\n';
  return 0;
}

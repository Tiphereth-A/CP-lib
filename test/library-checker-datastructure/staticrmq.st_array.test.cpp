#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../include/ds/st_array.hpp"

using namespace tifa_libs;
i32 f(i32 x, i32 y) { return std::min(x, y); }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  veci a(n);
  flt_ (u32, i, 0, n) std::cin >> a[i];
  ds::st_array<i32, f> st(a);
  for (u32 i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v;
    std::cout << st.query(u, v) << '\n';
  }
  return 0;
}

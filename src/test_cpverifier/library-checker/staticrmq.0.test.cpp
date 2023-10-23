#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../code/ds/st_array.hpp"

i32 f(i32 x, i32 y) { return std::min(x, y); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n, q;
  std::cin >> n >> q;
  vec<i32> a(n);
  for (size_t i = 0; i < n; ++i) std::cin >> a[i];
  tifa_libs::ds::st_array<i32, f> st(a);
  for (size_t i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v;
    std::cout << st.query(u, v - 1) << '\n';
  }
  return 0;
}

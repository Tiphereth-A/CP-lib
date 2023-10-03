#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "../../code/ds/st_0.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  tifa_libs::u32 n, q;
  std::cin >> n >> q;
  tifa_libs::vec<tifa_libs::i32> a(n);
  for (size_t i = 0; i < n; ++i) std::cin >> a[i];
  auto f = [](tifa_libs::i32 x, tifa_libs::i32 y) { return std::min(x, y); };
  tifa_libs::ds::sparse_table<tifa_libs::i32, decltype(f)> st(n, a, f);
  for (size_t i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v;
    std::cout << st.query(u, v - 1) << '\n';
  }
  return 0;
}

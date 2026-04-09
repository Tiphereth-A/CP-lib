// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/staticrmq
#include "../../../src/ds/rmq/linear/lib.hpp"

using namespace tifa_libs;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  veci a(n);
  flt_ (u32, i, 0, n) std::cin >> a[i];
  rmq_linear<i32, std::less<>> st(a);
  for (u32 i = 1, u, v; i <= q; ++i) {
    std::cin >> u >> v;
    std::cout << st.query(u, v - 1) << '\n';
  }
  return 0;
}

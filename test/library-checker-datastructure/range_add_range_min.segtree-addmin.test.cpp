#define PROBLEM "https://judge.yosupo.jp/problem/range_add_range_min"

#include "../../include/ds/segtree_ctor.hpp"
#include "../../include/io/ios_container.hpp"
#include "../../include/util/traits_math.hpp"

using namespace tifa_libs;

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, q;
  std::cin >> n >> q;
  vecii a(n);
  std::cin >> a;
  auto tr = ds::segtl_addmin_ctor<i64>(inf_v<i64>, a);
  flt_ (u32, i, 0, q) {
    u32 op, u, v;
    i64 w;
    std::cin >> op >> u >> v;
    if (op) std::cout << tr.query(u, v) << '\n';
    else (std::cin >> w), tr.update(u, v, w);
  }
  return 0;
}

#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3086"

#include "../../code/ds/segtree.hpp"
#include "../../code/opt/larsch.hpp"

i64 op(i64 x, i64 y) { return std::min(x, y); }
void mapping(i64& x, i64 y) { x = op(x, y); }

int main() {
  std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
  u32 n, L;
  std::cin >> n >> L;
  vecii a(n);
  for (auto& i : a) std::cin >> i, i = -i;
  const auto inf = tifa_libs::inf_v<i64>;
  tifa_libs::ds::segtree_notag<i64, op, mapping> tr(inf, a);
  auto ans = tifa_libs::opt::larsch<i64>(n, [&](u32 l, u32 r) { return r < l + L ? inf : tr.query(l, r); });
  std::cout << -ans.back() << '\n';
  return 0;
}

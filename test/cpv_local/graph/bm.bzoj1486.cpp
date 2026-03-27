// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1486

#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/sp/bm/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n, m;
  cin >> n >> m;
  graph::alistw<f64> g(n + 1);
  flt_ (u32, i, 0, m, u, v) {
    f64 w;
    cin >> u >> v >> w;
    g.add_arc(u, v, w);
  }
  f64 l = -1e7, r = 1e7, mid;
  auto chk = [&g](f64 x) {
    vec<f64> dis(g.size());
    flt_ (u32, i, 1, g.size())
      for (auto& [v, w] : g[i]) w -= x;
    bool flag = false;
    flt_ (u32, i, 1, g.size())
      if (!graph::bellman_ford(g, i, fn_0, dis)) {
        flag = true;
        break;
      }
    flt_ (u32, i, 1, g.size())
      for (auto& [v, w] : g[i]) w += x;
    return flag;
  };
  while (r - l > 1e-10) {
    mid = std::midpoint(l, r);
    (chk(mid) ? r : l) = mid;
  }
  cout << std::fixed << std::setprecision(8) << l << '\n';
}
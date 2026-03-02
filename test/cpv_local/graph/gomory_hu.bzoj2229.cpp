// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2229

#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/nf/gomory_hu/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 t;
  cin >> t;
  while (t--) {
    u32 n, m;
    cin >> n >> m;
    vec<edge_t<u64>> edges(m);
    for (auto& [w, u, v] : edges) {
      cin >> u >> v >> w;
      --u;
      --v;
    }
    graph::alistw<u64> mct(n);
    vvecuu mat(n, vecuu(n, std::numeric_limits<u64>::max()));
    for (auto mct_edges = graph::gomory_hu(n, edges); auto&& [w, u, v] : mct_edges) {
      mct.add_arc(u, v, w);
      mct.add_arc(v, u, w);
      mat[u][v] = mat[v][u] = w;
    }
    auto dfs = [&](auto&& dfs, u32 r, u32 u, u32 fa) -> void {
      for (auto [v, w] : mct.g[u])
        if (v != fa) mat[r][v] = std::min({mat[r][v], mat[r][u], w}), dfs(dfs, r, v, u);
      ;
    };
    flt_ (u32, r, 0, n) {
      dfs(dfs, r, r, -1_u32);
      mat[r][r] = 0;
    }
    map<u64, u32> cnts;
    flt_ (u32, i, 0, n)
      flt_ (u32, j, i + 1, n) ++cnts[mat[i][j]];
    u32 q;
    cin >> q;
    for (u32 i = 0, x; i < q; ++i) {
      cin >> x;
      u32 ans = 0;
      for (auto&& [k, v] : cnts) {
        if (k > x) break;
        ans += v;
      }
      cout << ans << '\n';
    }
    cout << '\n';
  }
}
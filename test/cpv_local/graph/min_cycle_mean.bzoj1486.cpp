// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1486

#include "../../../src/graph/min_cycle_mean/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n, m;
  cin >> n >> m;
  vec<edge_t<f64>> e(m);
  for (auto& [w, u, v] : e) cin >> u >> v >> w;
  cout << std::fixed << std::setprecision(8) << min_cycle_mean(e, n + 1) << '\n';
}
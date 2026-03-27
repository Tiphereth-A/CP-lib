// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1006

#include "../../../src/fast/rsort32/lib.hpp"
#include "../../../src/graph/chordal/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;

int main() {
  u32 n, m;
  cin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    cin >> u >> v;
    --u;
    --v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto& i : g.g) ::sort(i);
  graph::chordal chd(g);
  cout << chd.chromatic_number() << '\n';
}
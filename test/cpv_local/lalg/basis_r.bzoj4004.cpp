// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/4004

#include "../../../src/lalg/basis/r/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
struct Node {
  vec<double> v;
  int w;

  friend bool operator<(const Node& lhs, const Node& rhs) { retif_((lhs.w == rhs.w), lhs.v < rhs.v, lhs.w < rhs.w); }
};

int main() {
  set_eps(1e-4);
  vec<Node> a;
  u32 n, m;
  cin >> n >> m;
  basis_r<double> rbs(m);
  a.resize(n);
  for (auto& [v, w] : a) {
    v.resize(m);
    for (auto& j : v) cin >> j;
  }
  for (auto& [v, w] : a) cin >> w;
  std::sort(begin(a), end(a));
  int cnt = 0, ans = 0;
  for (auto&& [v, w] : a) {
    if (rbs.insert(v)) {
      ++cnt;
      ans += w;
    }
  }
  cout << cnt << ' ' << ans << '\n';
}
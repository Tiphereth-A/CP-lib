// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2731

#include "../../../src/edh/discretization/lib.hpp"
#include "../../../src/math/simpson/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
struct Node {
  int x, y, m;
  Node(int x = 0, int y = 0, int m = 0) : x(x), y(y), m(m) {}
};

vec<Node> v;
vecpt<data_t> seg;
template <class T>
T f(T pos) {
  seg.clear();
  for (auto [x, y, m] : v)
    if (x < pos && pos < x + m) seg.emplace_back(y, x + y + m - pos);
  if (seg.empty()) return 0;
  std::ranges::sort(seg);
  data_t ans = 0, lst = seg.front().first;
  for (auto&& [l, r] : seg)
    if (r - lst > 0) {
      ans += r - std::max(l, lst);
      lst = r;
    }
  return (T)ans;
}

CEXP data_t EPS = 1e-10l;

int main() {
  cout << std::fixed << std::setprecision(1);

  u32 n;
  cin >> n;
  v.clear();
  vec<Node> v_(n);
  for (auto& [x, y, m] : v_) cin >> y >> x >> m;
  std::ranges::sort(v_, [](Node CR l, Node CR r) { return l.m > r.m; });
  v.push_back(v_.front());
  flt_ (u32, i, 1, n) {
    auto&& now = v_[i];
    if (now.m == 0) break;
    if (std::ranges::none_of(v, [&now](Node CR x) { return now.x >= x.x && now.x + now.m <= x.x + x.m && now.y >= x.y && now.y + now.m <= x.y + x.m && now.x + now.y + now.m <= x.x + x.y + x.m; })) v.push_back(now);
  }
  seg.reserve(n);

  vec<int> pos;
  pos.reserve(n * 2);
  for (auto&& [x, _, m] : v) {
    pos.push_back(x);
    pos.push_back(x + m);
  }
  pos = uniq(pos);
  data_t ans = 0;
  math::simpson_impl<f64, f<f64>> integral;

  flt_ (u32, i, 1, (u32)pos.size()) ans += integral(pos[i - 1] + EPS, pos[i] - 2 * EPS, EPS);
  cout << ans << '\n';
}
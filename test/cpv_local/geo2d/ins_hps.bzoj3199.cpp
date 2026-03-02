// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/3199

#include "../../../src/geo2d/ins_hps/lib.hpp"
#include "../../../src/geo2d/proj/lib.hpp"
#include "../../../src/graph/ds/alist/lib.hpp"
#include "../../../src/graph/sp/dijkstra/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;

int main() {
  u32 t;
  cin >> t;
  while (t--) {
    u32 n;
    cin >> n;
    Point2 s, target;
    cin >> target >> s;
    vec<Point2> vp(n);
    for (auto& p : vp) cin >> p;
    if (!n) {
      cout << "0\n";
      continue;
    }
    map<Point2, u32> ids;
    flt_ (u32, i, 0, n) ids[vp[i]] = i + 1;
    u32 pos = 0;
    vecb skip(n);
    {
      data_t len = std::numeric_limits<data_t>::max();
      flt_ (u32, i, 0, n) {
        if (vp[i].x > target.x || vp[i].y > target.y) skip[i] = 1;
        if (data_t now = geo::dist_PP(vp[i], s); len > now) len = now, pos = i;
      }
    }
    vec<Line2> vl;
    vl.emplace_back(Point2(0, 0), Point2(target.x, 0));
    vl.emplace_back(Point2(target.x, 0), Point2(target.x, target.y));
    vl.emplace_back(Point2(target.x, target.y), Point2(0, target.y));
    vl.emplace_back(Point2(0, target.y), Point2(0, 0));
    graph::alistw<u32> g(n + 1);
    flt_ (u32, i, 0, n) {
      if (skip[i]) continue;
      vl.resize(4);
      flt_ (u32, j, 0, n) {
        if (j == i || skip[j]) continue;
        Point2 mid = mid_point(vp[i], vp[j]), v = rot90(vp[j] - vp[i]);
        vl.emplace_back(mid, mid + v);
      }
      auto res = geo::ins_hPs(vl);
      flt_ (u32, j, 0, res.size()) {
        Line2 l{res.vs[j], res.vs[res.next(j)]};
        u32 id = ids[reflect(l, vp[i])];
        if (id) --id;
        else id = n;
        g.add_arc(i, id, 1);
        g.add_arc(id, i, 1);
      }
    }
    cout << graph::dijkstra(g, pos, fn_0)[n] << '\n';
  }
}
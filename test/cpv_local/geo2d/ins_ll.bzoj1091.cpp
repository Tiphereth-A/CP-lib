// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1091

#include "../../../src/geo2d/dis/pp/lib.hpp"
#include "../../../src/geo2d/ins/ll/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using Line2 = line<data_t>;

int main() {
  cout << std::fixed << std::setprecision(3);

  u32 n, m;
  cin >> n >> m;
  vec<Line2> vl;
  vl.emplace_back(0, 0, n, 0);
  vl.emplace_back(n, 0, n, m);
  vl.emplace_back(n, m, 0, m);
  vl.emplace_back(0, m, 0, 0);
  u32 p;
  cin >> p;
  vec<Point2> vp(p);
  cin >> vp;
  vl.emplace_back(vp[0], vp[p - 1]);
  flt_ (u32, i, 0, p - 1) vl.emplace_back(vp[i + 1], vp[i]);
  std::sort(begin(vl) + 4, end(vl));
  data_t ans = std::numeric_limits<data_t>::max();
  Point2 INFP{1e5, 1e5};
  do {
    data_t now_ans = 0;
    flt_ (u32, i, 4, (u32)vl.size()) {
      Point2 l = INFP, r = INFP;
      flt_ (u32, j, 0, i) {
        if (!is_ins_LL(vl[i], vl[j])) continue;
        Point2 p = ins_LL(vl[i], vl[j]);
        if (p.x < 0 || p.y < 0 || p.x > n || p.y > m) continue;
        if (!is_lt(dist_PP(vl[i].l, p), dist_PP(vl[i].r, p)) && is_lt(dist_PP(vl[i].l, p), dist_PP(vl[i].l, l))) l = p;
        if (!is_lt(dist_PP(vl[i].r, p), dist_PP(vl[i].l, p)) && is_lt(dist_PP(vl[i].r, p), dist_PP(vl[i].r, r))) r = p;
      }
      now_ans += dist_PP(l, r);
    }
    ans = std::min(ans, now_ans);
  } while (std::next_permutation(begin(vl) + 4, end(vl)));
  cout << ans << '\n';
}
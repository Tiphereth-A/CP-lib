// competitive-verifier: LOCALCASE test/cpv_local/_data/codeforces/274C
// competitive-verifier: ERROR 0.0001

#include "../../../src/geo2d/ds/c/lib.hpp"
#include "../../../src/geo2d/pred/is_on_same_l/lib.hpp"
#include "../../../src/geo2d/proj/lib.hpp"
#include "../../../src/geo2d/tcenter/o/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using Circle2 = circle<data_t>;
using Triangle2 = triangle<data_t>;

int main() {
  cout << std::fixed << std::setprecision(20);

  set_eps<data_t>(1e-9);
  u32 n;
  cin >> n;
  set<Point2> exists;
  vec<Point2> vp;
  vp.reserve(n);
  data_t x, y;
  for (u32 i = 1; i <= n; ++i) {
    cin >> x >> y;
    exists.insert(Point2{x, y});
    vp.emplace_back(x, y);
  }
  struct Comp {
    bool operator()(const Circle2& lhs, const Circle2& rhs) const { retif_((lhs.o == rhs.o), lhs.r < rhs.r, lhs.o < rhs.o); }
  };
  set<Circle2, Comp> circles;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, i + 1, n)
      flt_ (u32, k, j + 1, n) {
        if (is_on_same_L(vp[i], vp[j], vp[k])) continue;
        Triangle2 t{vp[i], vp[j], vp[k]};
        if (t.is_obtuse()) continue;
        if (t.is_right()) {
          if (is_zero(dot(vp[i], vp[j], vp[k])) && exists.find(reflect({vp[j], vp[k]}, vp[i])) == end(exists)) continue;
          if (is_zero(dot(vp[j], vp[k], vp[i])) && exists.find(reflect({vp[k], vp[i]}, vp[j])) == end(exists)) continue;
          if (is_zero(dot(vp[k], vp[i], vp[j])) && exists.find(reflect({vp[i], vp[j]}, vp[k])) == end(exists)) continue;
        }
        circles.insert(Circle2{center_O(t), radius_O(t)});
      }
  data_t ans = -1;
  for (auto [o, r] : circles) {
    bool f = 0;
    for (auto CR p : vp)
      if ((f |= is_lt(dist_PP(p, o), r))) break;
    if (f) continue;
    ans = std::max(ans, r);
  }
  if (ans < 0) cout << "-1";
  else cout << ans;
}
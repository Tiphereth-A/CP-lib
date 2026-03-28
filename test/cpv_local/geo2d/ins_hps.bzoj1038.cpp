// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1038

#include "../../../src/geo2d/ins/ll/lib.hpp"
#include "../../../src/geo2d/ins_hps/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = point<data_t>;
using Line2 = line<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(3);
  set_eps<data_t>(1e-20);

  u32 n;
  cin >> n;
  vec<data_t> x(n), y(n);
  for (auto& i : x) cin >> i;
  for (auto& i : y) cin >> i;
  vec<Line2> vl;
  vl.emplace_back(x.front(), -1e12, x.back(), -1e12);
  vl.emplace_back(x.back(), -1e12, x.back(), 1e12);
  vl.emplace_back(x.back(), 1e12, x.front(), 1e12);
  vl.emplace_back(x.front(), 1e12, x.front(), -1e12);
  flt_ (u32, i, 0, n - 1) vl.emplace_back(x[i], y[i], x[i + 1], y[i + 1]);
  ConvexHull2 cvh = ins_hPs(vl);
  data_t ans = std::numeric_limits<data_t>::max();
  std::ranges::sort(cvh.vs, [](auto CR lhs, auto CR rhs) { return lhs.x < rhs.x; });
  u32 i = 0, j = 0;
  while (i < cvh.vs.size() && j < n) {
    if (i && is_eq(cvh[i].x, cvh[i - 1].x) && is_gt(cvh[i].y, cvh[i - 1].y)) {
      ++i;
      continue;
    }
    if (is_gt(cvh[i].x, x[j])) {
      Point2 temp = ins_LL(Line2{cvh[i], cvh[i - 1]}, Line2{Point2{x[j], y[j]}, Point2{x[j], y[j] + 1}});
      ans = std::min(ans, abs(temp.y - y[j++]));
    } else {
      if (!j) {
        ++i;
        continue;
      }
      Point2 temp = ins_LL(Line2{Point2{x[j - 1], y[j - 1]}, Point2{x[j], y[j]}}, Line2{cvh[i], Point2{cvh[i].x, cvh[i].y + 1}});
      ans = std::min(ans, abs(cvh[i++].y - temp.y));
    }
  }
  cout << ans << '\n';
}
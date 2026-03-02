// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2618

#include "../../../src/geo2d/ins_hps/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(3);

  u32 n, m;
  cin >> n;
  vec<Line2> vl;
  Point2 firstp, pre, now;
  for (u32 i = 1; i <= n; ++i) {
    cin >> m >> firstp;
    pre = firstp;
    for (u32 j = 1; j <= m - 1; ++j) {
      cin >> now;
      vl.emplace_back(pre, now);
      pre = now;
    }
    vl.emplace_back(now, firstp);
  }
  cout << geo::ins_hPs(vl).area() << '\n';
}
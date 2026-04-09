// competitive-verifier: LOCALCASE test/cpv_local/_data/loj/2549

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = point<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  u32 n, m, q;
  cin >> n >> m >> q;
  ConvexHull2 polya(n), polyb(m);
  cin >> polya >> polyb;
  for (auto& [x, y] : polyb.vs) {
    x = -x;
    y = -y;
  }
  polya.init();
  polyb.init();
  polya.do_minkowski_sum(polyb).init();
  flt_ (u32, i, 1, q + 1) {
    data_t x, y;
    cin >> x >> y;
    cout << polya.contains(Point2{x, y}) << '\n';
  }
}
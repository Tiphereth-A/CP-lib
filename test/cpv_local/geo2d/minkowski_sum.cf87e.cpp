// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/codeforces/87E

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

int main() {
  u32 a;
  cin >> a;
  ConvexHull2 poly(a);
  cin >> poly;
  poly.init();
  u32 b;
  cin >> b;
  ConvexHull2 poly2(b);
  cin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  u32 c;
  cin >> c;
  poly2.vs.resize(c);
  cin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  u32 n;
  cin >> n;
  data_t x, y;
  for (u32 i = 1; i <= n; ++i) {
    cin >> x >> y;
    cout << RES_YN[poly.contains(Point2{x * 3, y * 3})] << ' ';
  }
}
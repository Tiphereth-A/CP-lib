// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/11626

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

int main() {
  u32 t;
  cin >> t;
  while (t--) {
    u32 n;
    cin >> n;
    vec<Point2> v;
    data_t x, y;
    char c;
    flt_ (u32, i, 1, n + 1) {
      cin >> x >> y >> c;
      v.emplace_back(x, y);
    }
    ConvexHull2 got{v, false, false};
    u32 m;
    cin >> m;
    ConvexHull2 want(m);
    cin >> want;
    cout << (got.vs == want.vs ? "YES" : "NO") << '\n';
  }
}
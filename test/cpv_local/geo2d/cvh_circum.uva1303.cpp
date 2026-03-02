// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/1303

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

CEXP data_t PI = pi_v<data_t>;

int main() {
  cout << std::fixed << std::setprecision(0);

  u32 t;
  cin >> t;
  while (t--) {
    u32 n, l;
    cin >> n >> l;
    vec<Point2> vp(n);
    cin >> vp;
    cout << ConvexHull2{vp}.circum() + 2 * PI * l << '\n';
  }
}
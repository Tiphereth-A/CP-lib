// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/10652

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using ConvexHull2 = cvh<data_t>;

CEXP data_t PI = pi_v<data_t>;

int main() {
  cout << std::fixed << std::setprecision(1);

  u32 t;
  cin >> t;
  while (t--) {
    u32 n;
    cin >> n;
    vec<Point2> v;
    data_t x, y, w, h, phi;
    data_t ans = 0;
    flt_ (u32, i, 1, n + 1) {
      cin >> x >> y >> w >> h >> phi;
      phi = phi * PI / 180;
      if (phi < 0) phi += 2 * PI;
      phi = -phi;
      ans += w * h;
      Point2 c{x, y};
      v.emplace_back(c + Point2{w / 2, h / 2}.do_rot(phi));
      v.emplace_back(c + Point2{-w / 2, h / 2}.do_rot(phi));
      v.emplace_back(c + Point2{w / 2, -h / 2}.do_rot(phi));
      v.emplace_back(c + Point2{-w / 2, -h / 2}.do_rot(phi));
    }
    cout << ans * 100 / ConvexHull2{v}.init().area() << " %\n";
  }
}
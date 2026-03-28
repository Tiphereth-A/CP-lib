// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/2829

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using Line2 = line<data_t>;
using ConvexHull2 = cvh<data_t>;

CEXP data_t PI = std::numbers::pi_v<data_t>;

int main() {
  cout << std::fixed << std::setprecision(2);
  set_eps<data_t>(1e-9);

  u32 n;
  cin >> n;
  data_t a, b, r;
  cin >> b >> a >> r;
  Point2 d[4]{Point2{a / 2 - r, b / 2 - r}, Point2{-a / 2 + r, b / 2 - r}, Point2{a / 2 - r, -b / 2 + r}, Point2{-a / 2 + r, -b / 2 + r}};
  vec<Point2> vp;
  vp.reserve(n);
  data_t x, y, theta;
  for (u32 i = 1; i <= n; ++i) {
    cin >> x >> y >> theta;
    Point2 c{x, y};
    for (const auto& j : d) vp.push_back(c + rot(j, theta));
  }
  cout << ConvexHull2(vp).circum() + r * PI * 2 << '\n';
}
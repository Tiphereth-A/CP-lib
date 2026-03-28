// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/4445

#include "../../../src/geo2d/ins_hps/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = point<data_t>;
using Line2 = line<data_t>;
using Polygon2 = polygon<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(4);
  set_eps<data_t>(1e-18);

  u32 n;
  cin >> n;
  vec<Point2> vp(n);
  cin >> vp;
  vec<Line2> vl;
  vl.reserve(n * 2);
  vl.emplace_back(vp[0], vp[1]);
  flt_ (u32, i, 1, n, nexti) {
    nexti = (i + 1) % n;
    data_t a = vp[1].y - vp[0].y - vp[nexti].y + vp[i].y;
    data_t b = vp[0].x - vp[1].x - vp[i].x + vp[nexti].x;
    data_t c = vp[1].x * vp[0].y - vp[0].x * vp[1].y + vp[i].x * vp[nexti].y - vp[nexti].x * vp[i].y;
    vl.emplace_back(vp[i], vp[nexti]);
    if (!is_zero(a)) vl.emplace_back(-c / a, 0, b - c / a, -a);
    else if (!is_zero(b)) vl.emplace_back(0, -c / b, b, -a - c / b);
  }
  cout << ins_hPs(vl).area() / Polygon2{vp}.area() << '\n';
}
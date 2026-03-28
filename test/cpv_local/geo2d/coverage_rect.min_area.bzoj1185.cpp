// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1185

#include "../../../src/geo2d/rotcal/coverage_rect/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Polygon2 = polygon<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(5);

  u32 n;
  cin >> n;
  ConvexHull2 cvh(n);
  cin >> cvh;
  Polygon2 rect = coverage_rect<CVHRECT::min_area, data_t>(cvh.init());
  cout << rect.area() << '\n';
  u32 start = 0;
  flt_ (u32, i, 0, 4) {
    if (is_zero(rect[i].x)) rect[i].x = 0;
    if (is_zero(rect[i].y)) rect[i].y = 0;
  }
  flt_ (u32, i, 0, 4)
    if (is_lt(rect[i].y, rect[start].y) || (is_eq(rect[i].y, rect[start].y) && is_lt(rect[i].x, rect[start].x))) start = i;
  for (u32 i = start; i < 4; ++i) cout << rect[i] << '\n';
  for (u32 i = 0; i < start; ++i) cout << rect[i] << '\n';
}
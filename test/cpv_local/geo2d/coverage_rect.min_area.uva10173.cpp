// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/10173

#include "../../../src/geo2d/rotcal/coverage_rect/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(4);

  u32 n;
  while ((cin >> n), n) {
    ConvexHull2 cvh(n);
    cin >> cvh;
    cout << coverage_rect<CVHRECT::min_area, data_t>(cvh.init()).area() << '\n';
  }
}
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/109

#include "../../../src/geo2d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = point<data_t>;
using ConvexHull2 = cvh<data_t>;

int main() {
  cout << std::fixed << std::setprecision(2);

  vec<ConvexHull2> vpolys;
  int n;
  while ((cin >> n), ~n) {
    vpolys.emplace_back(n);
    cin >> vpolys.back();
    vpolys.back().init();
  }
  auto sz = vpolys.size();
  vecb destroyed(sz);
  kahan<data_t> destroyed_area = 0;
  Point2 missile;
  while (cin >> missile) {
    flt_ (usz, i, 0, sz)
      if (!destroyed[i] && vpolys[i].contains(missile)) {
        destroyed[i] = true;
        destroyed_area += vpolys[i].area();
      }
  }
  cout << destroyed_area << '\n';
}
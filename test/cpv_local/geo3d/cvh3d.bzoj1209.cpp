// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1209

#include "../../../src/geo3d/ds/cvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using point = point3d<data_t>;
using cvh = cvh3d<data_t>;

int main() {
  cout << std::fixed << std::setprecision(6);

  u32 n;
  cin >> n;
  vec<point> vp(n + 1);
  flt_ (u32, i, 1, n + 1) cin >> vp[i];
  cvh cvh(vp);
  cout << cvh.surface_area() << '\n';
}
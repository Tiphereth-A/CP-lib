// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1209

#include "../../../src/geo3d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using point = geo::point3d<data_t>;
using cvh = geo::cvh3d<data_t>;

rand::gen<u32> g(0, 1);

int main() {
  cout << std::fixed << std::setprecision(6);
  set_eps(1e-10);
  g.seed();

  u32 n;
  cin >> n;
  vec<point> vp(n + 1);
  flt_ (u32, i, 1, n + 1) cin >> vp[i];
  flt_ (u32, i, 1, n + 1) {
    vp[i].x += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].y += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].z += g() ? eps_v<data_t> : -eps_v<data_t>;
  }
  cvh cvh(vp);
  cout << cvh.surface_area() << '\n';
}
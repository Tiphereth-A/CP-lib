// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/bzoj/1591

#include "../../../src/geo2d/maxv_cvh_cnt/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;

int main() {
  u32 n;
  cin >> n;
  vec<Point2> vp(n);
  cin >> vp;
  cout << geo::maxv_cvh_cnt(vp) << '\n';
}
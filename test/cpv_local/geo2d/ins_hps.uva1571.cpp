// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/1571

#include "../../../src/geo2d/ins_hps/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

int main() {
  u32 n;
  while ((cin >> n), n) {
    vec<Point2> vp(n);
    cin >> vp;
    vec<Line2> vl;
    vl.emplace_back(vp.back(), vp.front());
    flt_ (u32, i, 0, n - 1) vl.emplace_back(vp[i], vp[i + 1]);
    ConvexHull2 cvh = geo::ins_hPs(vl);
    cout << (cvh.reunique().size() > 1) << '\n';
  }
}
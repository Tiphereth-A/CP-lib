// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/13024

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/io/container/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

int main() {
  u32 l;
  while (cin >> l) {
    vec<Point2> vpl(l);
    cin >> vpl;
    u32 s;
    cin >> s;
    vec<Point2> vps(s);
    cin >> vps;
    ConvexHull2 poly{vpl};
    cout << std::ranges::count_if(vps, [&poly](Point2 CR p) -> bool { return poly.contains(p); }) << '\n';
  }
}
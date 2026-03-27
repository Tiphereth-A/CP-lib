// competitive-verifier: LOCALCASE test/cpv_local/_data/codeforces/70D

#include "../../../src/geo2d/ds/dcvh/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f128;
using Point2 = geo::point<data_t>;
using DynamicCVH2 = geo::dcvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

int main() {
  u32 n;
  cin >> n;
  DynamicCVH2 dcvh;
  data_t x, y;
  flt_ (u32, i, 1, n + 1, t) {
    cin >> t >> x >> y;
    if (t == 1) dcvh.insert(Point2{x, y});
    else cout << RES_YN[dcvh.contains(Point2{x, y})] << ' ';
  }
}
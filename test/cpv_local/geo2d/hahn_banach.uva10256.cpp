// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/10256

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/geo2d/pred/is_ins_ss/lib.hpp"
#include "../../../src/geo2d/pred/is_on_s/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
using data_t = f64;
using Polygon2 = geo::cvh<data_t>;

const arr RES_Yn{"No"s, "Yes"s};

strn single_proceed(u32 n, u32 m) {
  Polygon2 poly1(n), poly2(m);
  cin >> poly1 >> poly2;
  poly1.init();
  poly2.init();
  for (auto CR i : poly1.vs)
    if (poly2.contains(i)) return RES_Yn[0];
  for (auto CR i : poly2.vs)
    if (poly1.contains(i)) return RES_Yn[0];
  if (poly1.size() > 1 && poly2.size() > 1) {
    for (auto it = begin(poly1.vs), itn = it + 1; it != end(poly1.vs); ++it, ++itn) {
      if (itn == end(poly1.vs)) itn = begin(poly1.vs);
      for (auto it2 = begin(poly2.vs), it2n = it2 + 1; it2 != end(poly2.vs); ++it2, ++it2n) {
        if (it2n == end(poly2.vs)) it2n = begin(poly2.vs);
        if (geo::is_ins_SS<data_t>({*it, *itn}, {*it2, *it2n})) return RES_Yn[0];
      }
    }
  } else {
    if (poly1.size() == 1 && poly2.size() == 1) return RES_Yn[!is_eq(poly1[0].x, poly2[0].x) || !is_eq(poly1[0].y, poly2[0].y)];
    if (poly1.size() == 1 && poly2.size() == 2) return RES_Yn[!geo::is_on_S<data_t>({poly2[0], poly2[1]}, poly1[0])];
    if (poly1.size() == 2 && poly2.size() == 1) return RES_Yn[!geo::is_on_S<data_t>({poly1[0], poly1[1]}, poly2[0])];
    if (poly1.size() == 2 && poly2.size() == 2) return RES_Yn[!geo::is_ins_SS<data_t>({poly1[0], poly1[1]}, {poly2[0], poly2[1]})];
  }
  return RES_Yn[1];
}

int main() {
  u32 n, m;
  while ((cin >> n >> m), n && m) cout << single_proceed(n, m) << '\n';
}
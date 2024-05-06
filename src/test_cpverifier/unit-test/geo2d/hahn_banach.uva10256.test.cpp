#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/is_ins_ss.hpp"
#include "../../../code/geo2d/rel_pop.hpp"
#include "../base.hpp"

using data_t = f64;
using Polygon2 = tifa_libs::geo::cvh<data_t>;

CEXP strn RES_Yn[2]{"No", "Yes"};

strn single_proceed(u32 n, u32 m, std::istream& fin) {
  Polygon2 poly1(n), poly2(m);
  fin >> poly1 >> poly2;
  poly1.init();
  poly2.init();
  for (auto CR i : poly1.vs)
    if (tifa_libs::geo::relation_CvhP(poly2, i) != tifa_libs::geo::outside_pop) return RES_Yn[0];
  for (auto CR i : poly2.vs)
    if (tifa_libs::geo::relation_CvhP(poly1, i) != tifa_libs::geo::outside_pop) return RES_Yn[0];
  if (poly1.size() > 1 && poly2.size() > 1) {
    for (auto it = poly1.vs.begin(), itn = it + 1; it != poly1.vs.end(); ++it, ++itn) {
      if (itn == poly1.vs.end()) itn = poly1.vs.begin();
      for (auto it2 = poly2.vs.begin(), it2n = it2 + 1; it2 != poly2.vs.end(); ++it2, ++it2n) {
        if (it2n == poly2.vs.end()) it2n = poly2.vs.begin();
        if (tifa_libs::geo::is_ins_SS<data_t>({*it, *itn}, {*it2, *it2n})) return RES_Yn[0];
      }
    }
  } else {
    if (poly1.size() == 1 && poly2.size() == 1) return RES_Yn[!tifa_libs::is_eq(poly1[0].x, poly2[0].x) || !tifa_libs::is_eq(poly1[0].y, poly2[0].y)];
    if (poly1.size() == 1 && poly2.size() == 2) return RES_Yn[!tifa_libs::geo::is_on_S<data_t>({poly2[0], poly2[1]}, poly1[0])];
    if (poly1.size() == 2 && poly2.size() == 1) return RES_Yn[!tifa_libs::geo::is_on_S<data_t>({poly1[0], poly1[1]}, poly2[0])];
    if (poly1.size() == 2 && poly2.size() == 2) return RES_Yn[!tifa_libs::geo::is_ins_SS<data_t>({poly1[0], poly1[1]}, {poly2[0], poly2[1]})];
  }
  return RES_Yn[1];
}

void test(strn CR data) {
  strn path = "src/data/uva/10256/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n, m;
  u32 testcase = 0;
  while ((fin >> n >> m), n && m) {
    ++testcase;
    strn got = single_proceed(n, m, fin);
    strn want;
    std::getline(fans, want);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: break;
    case tifa_libs::unittest::ts_random_01: break;
    case tifa_libs::unittest::ts_random_02: break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
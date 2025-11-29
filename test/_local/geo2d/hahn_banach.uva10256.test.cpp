#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
#include "../../../include/geo2d/is_ins_ss.hpp"
#include "../../../include/geo2d/is_on_s.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Polygon2 = geo::cvh<data_t>;

CEXP arr RES_Yn{"No"s, "Yes"s};

strn single_proceed(u32 n, u32 m, std::istream& fin) {
  Polygon2 poly1(n), poly2(m);
  fin >> poly1 >> poly2;
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

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "10256", data);
  std::ifstream fin(fn_in), fans(fn_ans);

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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: break;
    case unittest::TC::random_01: break;
    case unittest::TC::random_02: break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}
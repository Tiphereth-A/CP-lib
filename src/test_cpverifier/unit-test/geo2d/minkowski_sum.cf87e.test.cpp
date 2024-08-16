#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"
#include "../base.hpp"

using data_t = f128;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

u32 n;
strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 a, b, c;
  fin >> a;
  ConvexHull2 poly(a);
  fin >> poly;
  poly.init();
  fin >> b;
  ConvexHull2 poly2(b);
  fin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  fin >> c;
  poly2.vs.resize(c);
  fin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  fin >> n;
  data_t x, y;
  for (u32 i = 1; i <= n; ++i) {
    fin >> x >> y;
    ss << RES_YN[poly.contains(Point2{x * 3, y * 3})] << ' ';
  }

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("codeforces", "87E", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, n) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
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
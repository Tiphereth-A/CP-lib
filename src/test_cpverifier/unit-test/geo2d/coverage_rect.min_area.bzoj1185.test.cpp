#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/coverage_rect.hpp"

#include "../base.hpp"

using data_t = f64;
using Polygon2 = tifa_libs::geo::polygon<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(5);

  u32 n;
  fin >> n;
  ConvexHull2 cvh(n);
  fin >> cvh;
  Polygon2 rect = tifa_libs::geo::coverage_rect<tifa_libs::geo::CR_MIN_AREA, data_t>(cvh.init());
  ss << rect.area() << ' ';
  u32 start = 0;
  flt_ (u32, i, 0, 4) {
    if (tifa_libs::is_zero(rect[i].x)) rect[i].x = 0;
    if (tifa_libs::is_zero(rect[i].y)) rect[i].y = 0;
  }
  flt_ (u32, i, 0, 4)
    if (tifa_libs::is_lt(rect[i].y, rect[start].y) || (tifa_libs::is_eq(rect[i].y, rect[start].y) && tifa_libs::is_lt(rect[i].x, rect[start].x))) start = i;
  for (u32 i = start; i < 4; ++i) ss << rect[i] << ' ';
  for (u32 i = 0; i < start; ++i) ss << rect[i] << ' ';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "1185", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, 5) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
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
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
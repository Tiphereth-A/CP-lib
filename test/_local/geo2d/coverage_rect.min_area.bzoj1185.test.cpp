#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/coverage_rect.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Polygon2 = geo::polygon<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(5);

  u32 n;
  fin >> n;
  ConvexHull2 cvh(n);
  fin >> cvh;
  Polygon2 rect = geo::coverage_rect<geo::CVHRECT::min_area, data_t>(cvh.init());
  ss << rect.area() << ' ';
  u32 start = 0;
  flt_ (u32, i, 0, 4) {
    if (is_zero(rect[i].x)) rect[i].x = 0;
    if (is_zero(rect[i].y)) rect[i].y = 0;
  }
  flt_ (u32, i, 0, 4)
    if (is_lt(rect[i].y, rect[start].y) || (is_eq(rect[i].y, rect[start].y) && is_lt(rect[i].x, rect[start].x))) start = i;
  for (u32 i = start; i < 4; ++i) ss << rect[i] << ' ';
  for (u32 i = 0; i < start; ++i) ss << rect[i] << ' ';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1185", data);
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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: test("3"); break;
    case unittest::TC::random_01: test("4"); break;
    case unittest::TC::random_02: test("5"); break;
    case unittest::TC::random_03: test("6"); break;
    case unittest::TC::random_04: test("7"); break;
    case unittest::TC::random_05: test("8"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}
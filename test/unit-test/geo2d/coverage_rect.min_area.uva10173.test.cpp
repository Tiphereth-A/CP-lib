#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/coverage_rect.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(u32 n, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  ConvexHull2 cvh(n);
  fin >> cvh;
  ss << geo::coverage_rect<geo::CR_MIN_AREA, data_t>(cvh.init()).area() << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "10173", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  u32 testcase = 0;
  while ((fin >> n), n) {
    ++testcase;
    strn got = single_proceed(n, fin);
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
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: break;
    case unittest::ts_random_01: break;
    case unittest::ts_random_02: break;
    case unittest::ts_random_03: break;
    case unittest::ts_random_04: break;
    case unittest::ts_random_05: break;
    case unittest::ts_random_06: break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
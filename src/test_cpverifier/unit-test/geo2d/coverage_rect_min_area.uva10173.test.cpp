#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/coverage_rect_min_area.hpp"

#include "../base.hpp"

using data_t = f128;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(u32 n, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  ConvexHull2 cvh(n);
  fin >> cvh;
  ss << tifa_libs::geo::coverage_rect_min_area(cvh.init()).area() << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/uva/10173/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

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
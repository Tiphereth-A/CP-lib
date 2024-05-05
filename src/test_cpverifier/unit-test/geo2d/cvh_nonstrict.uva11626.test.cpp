#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"
#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

ConvexHull2 single_proceed(std::istream& fin) {
  u32 n;
  fin >> n;
  vec<Point2> v;
  data_t x, y;
  char c;
  fle_ (u32, i, 1, n) {
    fin >> x >> y >> c;
    v.emplace_back(x, y);
  }
  return ConvexHull2{v, false, false};
}

void test(strn CR data) {
  strn path = "src/data/uva/11626/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 t;
  u32 testcase = 0;
  fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    auto got = single_proceed(fin);
    u32 n;
    fans >> n;
    ConvexHull2 want(n);
    fans >> want;
    check(got.vs, want.vs, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
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
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/ins_hps.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  u32 n, m;
  fin >> n;
  vec<Line2> vl;
  Point2 firstp, pre, now;
  for (u32 i = 1; i <= n; ++i) {
    fin >> m >> firstp;
    pre = firstp;
    for (u32 j = 1; j <= m - 1; ++j) {
      fin >> now;
      vl.emplace_back(pre, now);
      pre = now;
    }
    vl.emplace_back(now, firstp);
  }
  ss << tifa_libs::geo::ins_hPs(vl).area();

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/bzoj/2618/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
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
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
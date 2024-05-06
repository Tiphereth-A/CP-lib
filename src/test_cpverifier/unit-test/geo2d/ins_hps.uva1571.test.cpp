#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/ins_hps.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(u32 n, std::istream& fin) {
  std::stringstream ss;

  vec<Point2> vp(n);
  fin >> vp;
  vec<Line2> vl;
  vl.emplace_back(vp.back(), vp.front());
  fle_ (u32, i, 0, n - 2) vl.emplace_back(vp[i], vp[i + 1]);
  ConvexHull2 cvh = tifa_libs::geo::ins_hPs(vl);
  ss << (cvh.reunique().size() > 1) << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/uva/1571/" + data;
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
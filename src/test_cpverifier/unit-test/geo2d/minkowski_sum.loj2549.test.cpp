#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"
#include "../../../code/geo2d/rel_pop.hpp"
#include "../base.hpp"

using data_t = f128;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

u32 q;
strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m >> q;
  ConvexHull2 polya(n), polyb(m);
  fin >> polya >> polyb;
  for (auto &[x, y] : polyb.vs) {
    x = -x;
    y = -y;
  }
  polya.init();
  polyb.init();
  polya.do_minkowski_sum(polyb);
  fle_ (u32, i, 1, q) {
    data_t x, y;
    fin >> x >> y;
    auto res = tifa_libs::geo::relation_CvhP(polya, Point2{x, y});
    ss << (res != tifa_libs::geo::outside_pop) << ' ';
  }

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/loj/2549/war" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, q) {
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
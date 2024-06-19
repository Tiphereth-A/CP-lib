#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/cvh.hpp"
#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  vec<ConvexHull2> vpolys;
  int n;
  while ((fin >> n), ~n) {
    vpolys.emplace_back(n);
    fin >> vpolys.back();
    vpolys.back().init();
  }
  auto sz = vpolys.size();
  vecb destroied(sz);
  tifa_libs::math::kahan<data_t> destroied_area = 0;
  Point2 missile;
  while (fin >> missile) {
    flt_ (usz, i, 0, sz)
      if (!destroied[i] && vpolys[i].contains(missile)) {
        destroied[i] = true;
        destroied_area += vpolys[i].area();
      }
  }
  ss << destroied_area << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/uva/109/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  strn got = single_proceed(fin);
  strn want;
  std::getline(fans, want);
  while (isspace(got.back())) got.pop_back();
  while (isspace(want.back())) want.pop_back();
  check(got, want);
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
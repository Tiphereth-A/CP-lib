#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo3d/cvh3d.hpp"

#include "../base.hpp"

using data_t = f128;
using point = tifa_libs::geo::point3d<data_t>;
using cvh = tifa_libs::geo::cvh3d<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(6);

  set_eps(1e-10);
  u32 n;
  fin >> n;
  tifa_libs::rand::Gen<std::uniform_int_distribution<u32>> g(0, 1);
  g.reset_seed();
  vec<point> vp(n + 1);
  fle_ (u32, i, 1, n) fin >> vp[i];
  fle_ (u32, i, 1, n) {
    vp[i].x += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].y += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].z += g() ? eps_v<data_t> : -eps_v<data_t>;
  }
  cvh cvh(vp);
  ss << cvh.surface_area() << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/bzoj/1209/" + data;
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
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using ConvexHull2 = tifa_libs::geo::cvh<data_t>;

strn single_proceed(u32 l, std::istream& fin) {
  std::stringstream ss;

  vec<Point2> vpl(l);
  fin >> vpl;
  u32 s;
  fin >> s;
  vec<Point2> vps(s);
  fin >> vps;
  ConvexHull2 poly{vpl};
  ss << std::ranges::count_if(vps, [&poly](Point2 CR p) -> bool { return poly.contains(p); }) << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("uva", "13024", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 l;
  u32 testcase = 0;
  while (fin >> l) {
    ++testcase;
    strn got = single_proceed(l, fin);
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
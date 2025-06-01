#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/ins_hps.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

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
  ss << geo::ins_hPs(vl).area();

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "2618", data);
  std::ifstream fin(fn_in), fans(fn_ans);

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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: test("3"); break;
    case unittest::ts_random_01: test("4"); break;
    case unittest::ts_random_02: test("5"); break;
    case unittest::ts_random_03: test("6"); break;
    case unittest::ts_random_04: test("7"); break;
    case unittest::ts_random_05: test("8"); break;
    case unittest::ts_random_06: test("9"); break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
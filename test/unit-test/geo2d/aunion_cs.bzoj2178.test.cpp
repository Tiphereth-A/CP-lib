#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/aunion_cs.hpp"

#include "../../../include/edh/discretization.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Circle2 = geo::circle<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  u32 n;
  fin >> n;
  vec<Circle2> cs(n);
  fin >> cs;
  auto res = geo::aunion_Cs(uniq(cs));
  ss << res[0];

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "2178", data);
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
    case unittest::ts_example_00: test("1"), test("13"); break;
    case unittest::ts_example_01: test("2"), test("14"); break;
    case unittest::ts_random_00: test("3"), test("15"); break;
    case unittest::ts_random_01: test("4"), test("16"); break;
    case unittest::ts_random_02: test("5"), test("17"); break;
    case unittest::ts_random_03: test("6"); break;
    case unittest::ts_random_04: test("7"); break;
    case unittest::ts_random_05: test("8"); break;
    case unittest::ts_random_06: test("9"); break;
    case unittest::ts_random_07: test("10"); break;
    case unittest::ts_random_08: test("11"); break;
    case unittest::ts_random_09: test("12"); break;
    default: break;
  }

  unittest::post_test();
}
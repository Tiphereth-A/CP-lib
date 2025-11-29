#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/dcvh.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using Point2 = geo::point<data_t>;
using DynamicCVH2 = geo::dcvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

u32 n;
strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  fin >> n;
  DynamicCVH2 dcvh;
  data_t x, y;
  for (u32 i = 1, t; i <= n; ++i) {
    fin >> t >> x >> y;
    if (t == 1) dcvh.insert(Point2{x, y});
    else ss << RES_YN[dcvh.contains(Point2{x, y})] << ' ';
  }

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("codeforces", "70D", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, n) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"), test("13"), test("25"), test("37"), test("49"); break;
    case unittest::TC::example_01: test("2"), test("14"), test("26"), test("38"), test("50"); break;
    case unittest::TC::random_00: test("3"), test("15"), test("27"), test("39"), test("51"); break;
    case unittest::TC::random_01: test("4"), test("16"), test("28"), test("40"), test("52"); break;
    case unittest::TC::random_02: test("5"), test("17"), test("29"), test("41"); break;
    case unittest::TC::random_03: test("6"), test("18"), test("30"), test("42"); break;
    case unittest::TC::random_04: test("7"), test("19"), test("31"), test("43"); break;
    case unittest::TC::random_05: test("8"), test("20"), test("32"), test("44"); break;
    case unittest::TC::random_06: test("9"), test("21"), test("33"), test("45"); break;
    case unittest::TC::random_07: test("10"), test("22"), test("34"), test("46"); break;
    case unittest::TC::random_08: test("11"), test("23"), test("35"), test("47"); break;
    case unittest::TC::random_09: test("12"), test("24"), test("36"), test("48"); break;
    default: break;
  }

  unittest::post_test();
}
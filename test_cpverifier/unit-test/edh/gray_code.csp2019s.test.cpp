#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/gray_code.hpp"

#include "../base.hpp"

strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  u64 k;
  fin >> n >> k;
  auto x = tifa_libs::gray_code(n, k).to_string().substr(64 - n);
  ss << x;

  return ss.str();
}

void test(strn CR data) {
  strn path = "data/csp/2019s/code" + data;
  std::ifstream fin(path + ".in"), fans(path + ".ans");

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
    case tifa_libs::unittest::ts_example_00: test("1"), test("13"); break;
    case tifa_libs::unittest::ts_example_01: test("2"), test("14"); break;
    case tifa_libs::unittest::ts_random_00: test("3"), test("15"); break;
    case tifa_libs::unittest::ts_random_01: test("4"), test("16"); break;
    case tifa_libs::unittest::ts_random_02: test("5"), test("17"); break;
    case tifa_libs::unittest::ts_random_03: test("6"), test("18"); break;
    case tifa_libs::unittest::ts_random_04: test("7"), test("19"); break;
    case tifa_libs::unittest::ts_random_05: test("8"), test("20"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: test("11"); break;
    case tifa_libs::unittest::ts_random_09: test("12"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/edh/gray_code.hpp"

#include "../base.hpp"

using namespace tifa_libs;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  u64 k;
  fin >> n >> k;
  auto x = gray_code(n, k).to_string().substr(64 - n);
  ss << x;

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("csp", "2019s", "code"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  strn got = single_proceed(fin);
  strn want;
  std::getline(fans, want);
  while (isspace(got.back())) got.pop_back();
  while (isspace(want.back())) want.pop_back();
  check(got, want);
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"), test("13"); break;
    case unittest::TC::example_01: test("2"), test("14"); break;
    case unittest::TC::random_00: test("3"), test("15"); break;
    case unittest::TC::random_01: test("4"), test("16"); break;
    case unittest::TC::random_02: test("5"), test("17"); break;
    case unittest::TC::random_03: test("6"), test("18"); break;
    case unittest::TC::random_04: test("7"), test("19"); break;
    case unittest::TC::random_05: test("8"), test("20"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: test("11"); break;
    case unittest::TC::random_09: test("12"); break;
    default: break;
  }

  unittest::post_test();
}
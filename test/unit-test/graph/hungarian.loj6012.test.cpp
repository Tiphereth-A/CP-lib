#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/graph/hungarian.hpp"

#include "../base.hpp"

using namespace tifa_libs;
strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  vveci c1(n, veci(n));
  for (auto &i : c1) fin >> i;
  auto c2 = c1;
  for (auto &i : c2)
    for (auto &j : i) j = -j;
  ss << graph::hungarian(c1).back() << '\n';
  ss << -graph::hungarian(c2).back() << '\n';

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "6012", "job" + data);
  std::ifstream fin(fn_in), fans(fn_ans);

  {
    strn got = single_proceed(fin);
    strn want, want2;
    std::getline(fans, want);
    std::getline(fans, want2);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    while (isspace(want2.back())) want2.pop_back();
    want = want + '\n' + want2;
    check(got, want);
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("0"); break;
    case unittest::ts_example_01: test("1"); break;
    case unittest::ts_random_00: test("2"); break;
    case unittest::ts_random_01: test("3"); break;
    case unittest::ts_random_02: test("4"); break;
    case unittest::ts_random_03: test("5"); break;
    case unittest::ts_random_04: test("6"); break;
    case unittest::ts_random_05: test("7"); break;
    case unittest::ts_random_06: test("8"); break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/graph/hungarian.hpp"

#include "../base.hpp"

strn single_proceed(std::istream &fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  vvec<i32> c1(n, vec<i32>(n));
  for (auto &i : c1) fin >> i;
  auto c2 = c1;
  for (auto &i : c2)
    for (auto &j : i) j = -j;
  ss << tifa_libs::graph::hungarian(c1).back() << '\n';
  ss << -tifa_libs::graph::hungarian(c2).back() << '\n';

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/loj/6012/job" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

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
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("0"); break;
    case tifa_libs::unittest::ts_example_01: test("1"); break;
    case tifa_libs::unittest::ts_random_00: test("2"); break;
    case tifa_libs::unittest::ts_random_01: test("3"); break;
    case tifa_libs::unittest::ts_random_02: test("4"); break;
    case tifa_libs::unittest::ts_random_03: test("5"); break;
    case tifa_libs::unittest::ts_random_04: test("6"); break;
    case tifa_libs::unittest::ts_random_05: test("7"); break;
    case tifa_libs::unittest::ts_random_06: test("8"); break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
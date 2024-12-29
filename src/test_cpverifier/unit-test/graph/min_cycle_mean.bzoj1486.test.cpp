#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/graph/min_cycle_mean.hpp"

#include "../base.hpp"

u32 q;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m;
  vec<edge_t<f64>> e(m);
  for (auto& [w, u, v] : e) fin >> u >> v >> w;
  ss << std::fixed << std::setprecision(8) << tifa_libs::graph::min_cycle_mean(e, n + 1);

  return ss.str();
}

void test(strn data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "1486", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  strn got = single_proceed(fin);
  while (isspace(got.back())) got.pop_back();
  strn want;
  std::getline(fans, want);
  while (isspace(want.back())) want.pop_back();
  check(got, want);
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
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/graph/chordal.hpp"

#include "../base.hpp"

void test(strn const& data) {
  strn path = "src/data/bzoj/1006/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  u32 n, m;
  fin >> n >> m;
  tifa_libs::graph::alist<> g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    fin >> u >> v;
    --u;
    --v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto& i : g.g) std::ranges::sort(i);
  tifa_libs::graph::chordal<> chd(g);
  u32 got = chd.chromatic_number();
  u32 want;
  fans >> want;
  check(got, want, check_param(data));
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
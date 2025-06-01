#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/graph/chordal.hpp"

#include "../../../include/fast/rsort32.hpp"
#include "../../../include/graph/alist.hpp"
#include "../base.hpp"

using namespace tifa_libs;
void test(strn data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1006", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n, m;
  fin >> n >> m;
  graph::alist g(n);
  for (u32 i = 0, u, v; i < m; ++i) {
    fin >> u >> v;
    --u;
    --v;
    g.add_arc(u, v);
    g.add_arc(v, u);
  }
  for (auto& i : g.g) ::sort(i);
  graph::chordal chd(g);
  u32 got = chd.chromatic_number();
  u32 want;
  fans >> want;
  check(got, want, check_param(data));
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
    case unittest::ts_random_07: test("10"); break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
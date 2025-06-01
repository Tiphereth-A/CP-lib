#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/ds/st_array.hpp"

#include "../base.hpp"

using namespace tifa_libs;
i64 f(i64 x, i64 y) { return std::max(x, y); }

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1012", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 m, d;
  fin >> m >> d;
  ds::st_array<i64, f> st;
  char op;
  i64 t = 0, u;
  for (u32 i = 1; i <= m; ++i) {
    fin >> op >> u;
    if (op == 'A') st.push_back((u % d + t + d) % d);
    else {
      t = st.query(u32(st.size() - u));
      i64 ans_t;
      fans >> ans_t;
      check(t, ans_t, check_param(i));
    }
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
    case unittest::ts_random_06: break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
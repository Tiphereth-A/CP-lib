#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/ds/mono_stack.hpp"

#include "../base.hpp"

using namespace tifa_libs;
// vecu a;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  ds::mono_stack<u32, std::greater_equal<u32>> stk;
  u64 ans = 0;
  flt_ (u32, i, 0, n, x) {
    fin >> x;
    stk.pop_greater(x);
    ans += stk.size();
    stk.push_nocheck(x);
  }
  ss << ans;

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1660", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want, _;
    while (std::getline(fans, _)) want += _ + '\n';
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
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
    case unittest::ts_random_06: test("9"); break;
    case unittest::ts_random_07: test("10"); break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
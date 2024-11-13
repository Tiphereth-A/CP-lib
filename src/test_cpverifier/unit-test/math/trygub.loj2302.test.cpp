#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/math/trygub.hpp"

#include "../base.hpp"

vecii single_proceed(std::istream &fin) {
  std::stringstream ss;

  vecii ans;
  u32 n, t1, t2, t3;
  fin >> n >> t1 >> t2 >> t3;
  tifa_libs::math::trygub_num<2> num;
  flt_ (u32, i, 0, n) {
    int op;
    fin >> op;
    if (op == 1) {
      int a, b;
      fin >> a >> b;
      num.add(a, b);
    } else {
      int k;
      fin >> k;
      ans.push_back(num.get(k));
    }
  }

  return ans;
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("loj", "2302", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    vecii got = single_proceed(fin);
    vecii want(got.size());
    flt_ (u32, i, 0, (u32)got.size()) fans >> want[i];
    while (isspace(fans.peek())) fans.get();
    check_bool(fans.eof(), check_param(testcase), check_param(got.size()));
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("integer1"), test("integer13"), test("integer25"); break;
    case tifa_libs::unittest::ts_example_01: test("integer2"), test("integer14"); break;
    case tifa_libs::unittest::ts_random_00: test("integer3"), test("integer15"); break;
    case tifa_libs::unittest::ts_random_01: test("integer4"), test("integer16"); break;
    case tifa_libs::unittest::ts_random_02: test("integer5"), test("integer17"); break;
    case tifa_libs::unittest::ts_random_03: test("integer6"), test("integer18"); break;
    case tifa_libs::unittest::ts_random_04: test("integer7"), test("integer19"); break;
    case tifa_libs::unittest::ts_random_05: test("integer8"), test("integer20"); break;
    case tifa_libs::unittest::ts_random_06: test("integer9"), test("integer21"); break;
    case tifa_libs::unittest::ts_random_07: test("integer10"), test("integer22"); break;
    case tifa_libs::unittest::ts_random_08: test("integer11"), test("integer23"); break;
    case tifa_libs::unittest::ts_random_09: test("integer12"), test("integer24"); break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
// competitive-verifier: STANDALONE

#include "../../../src/math/ds/trygub/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
vecii single_proceed(std::istream& fin) {
  std::stringstream ss;

  vecii ans;
  u32 n, t1, t2, t3;
  fin >> n >> t1 >> t2 >> t3;
  math::trygub_num<2> num;
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

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "2302", data);
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
  for (int i = 1; i <= 25; ++i) {
    timer_(test("integer"s + std::to_string(i)));
  }
}
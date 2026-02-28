// competitive-verifier: STANDALONE

#include "../../../src/ds/mono_stack/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;

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

void test(strnv data) {
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
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}
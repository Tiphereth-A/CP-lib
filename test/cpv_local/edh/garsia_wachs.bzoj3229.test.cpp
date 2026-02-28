// competitive-verifier: STANDALONE

#include "../../../src/edh/garsia_wachs/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  vecu v(n + 2);
  flt_ (u32, i, 1, n + 1) fin >> v[i];
  v[0] = v[n + 1] = 0x3f3f3f3f;
  u32 ans = 0;
  garsia_wachs(v, [&](u32, u32, u32, u32, u32 a) { ans += a; });
  ss << ans << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "3229", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want;
    std::getline(fans, want);
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
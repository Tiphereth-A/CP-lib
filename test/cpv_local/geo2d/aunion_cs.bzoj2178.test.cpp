// competitive-verifier: STANDALONE

#include "../../../src/edh/discretization/lib.hpp"
#include "../../../src/geo2d/aunion/cs/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Circle2 = geo::circle<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  u32 n;
  fin >> n;
  vec<Circle2> cs(n);
  fin >> cs;
  auto res = geo::aunion_Cs(uniq(cs));
  ss << res[0];

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "2178", data);
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
  for (int i = 1; i <= 17; ++i) {
    timer_(test(std::to_string(i)));
  }
}
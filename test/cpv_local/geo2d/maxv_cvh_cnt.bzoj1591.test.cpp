// competitive-verifier: STANDALONE

#include "../../../src/geo2d/maxv_cvh_cnt/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n;
  fin >> n;
  vec<Point2> vp(n);
  fin >> vp;
  ss << geo::maxv_cvh_cnt(vp);

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1591", data);
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
  for (int i = 1; i <= 20; ++i) {
    timer_(test(std::to_string(i)));
  }
}
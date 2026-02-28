// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ins_hps/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  u32 n, m;
  fin >> n;
  vec<Line2> vl;
  Point2 firstp, pre, now;
  for (u32 i = 1; i <= n; ++i) {
    fin >> m >> firstp;
    pre = firstp;
    for (u32 j = 1; j <= m - 1; ++j) {
      fin >> now;
      vl.emplace_back(pre, now);
      pre = now;
    }
    vl.emplace_back(now, firstp);
  }
  ss << geo::ins_hPs(vl).area();

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "2618", data);
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
  for (int i = 1; i <= 9; ++i) {
    timer_(test(std::to_string(i)));
  }
}
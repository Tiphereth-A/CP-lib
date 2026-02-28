// competitive-verifier: STANDALONE

#include "../../../src/geo2d/rotcal/coverage_rect/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(u32 n, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  ConvexHull2 cvh(n);
  fin >> cvh;
  ss << geo::coverage_rect<geo::CVHRECT::min_area, data_t>(cvh.init()).area() << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "10173", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 n;
  u32 testcase = 0;
  while ((fin >> n), n) {
    ++testcase;
    strn got = single_proceed(n, fin);
    strn want;
    std::getline(fans, want);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  for (int i = 1; i <= 2; ++i) {
    timer_(test(std::to_string(i)));
  }
}
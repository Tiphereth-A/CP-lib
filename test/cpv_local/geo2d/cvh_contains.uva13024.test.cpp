// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(u32 l, std::istream& fin) {
  std::stringstream ss;

  vec<Point2> vpl(l);
  fin >> vpl;
  u32 s;
  fin >> s;
  vec<Point2> vps(s);
  fin >> vps;
  ConvexHull2 poly{vpl};
  ss << std::ranges::count_if(vps, [&poly](Point2 CR p) -> bool { return poly.contains(p); }) << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "13024", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 l;
  u32 testcase = 0;
  while (fin >> l) {
    ++testcase;
    strn got = single_proceed(l, fin);
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
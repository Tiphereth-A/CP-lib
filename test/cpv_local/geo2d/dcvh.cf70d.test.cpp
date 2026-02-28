// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/dcvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using Point2 = geo::point<data_t>;
using DynamicCVH2 = geo::dcvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

u32 n;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  fin >> n;
  DynamicCVH2 dcvh;
  data_t x, y;
  for (u32 i = 1, t; i <= n; ++i) {
    fin >> t >> x >> y;
    if (t == 1) dcvh.insert(Point2{x, y});
    else ss << RES_YN[dcvh.contains(Point2{x, y})] << ' ';
  }

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("codeforces", "70D", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, n) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  for (int i = 1; i <= 52; ++i) {
    timer_(test(std::to_string(i)));
  }
}
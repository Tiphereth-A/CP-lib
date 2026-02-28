// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

const strn RES_YN[2] = {"NO", "YES"};

u32 n;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 a, b, c;
  fin >> a;
  ConvexHull2 poly(a);
  fin >> poly;
  poly.init();
  fin >> b;
  ConvexHull2 poly2(b);
  fin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  fin >> c;
  poly2.vs.resize(c);
  fin >> poly2;
  poly.do_minkowski_sum(poly2.init()).init();
  fin >> n;
  data_t x, y;
  for (u32 i = 1; i <= n; ++i) {
    fin >> x >> y;
    ss << RES_YN[poly.contains(Point2{x * 3, y * 3})] << ' ';
  }

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("codeforces", "87E", data);
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
  for (int i = 1; i <= 5; ++i) {
    timer_(test(std::to_string(i)));
  }
}
// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

CEXP data_t PI = std::numbers::pi_v<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  set_eps<data_t>(1e-9);
  u32 n;
  fin >> n;
  data_t a, b, r;
  fin >> b >> a >> r;
  Point2 d[4]{Point2{a / 2 - r, b / 2 - r}, Point2{-a / 2 + r, b / 2 - r}, Point2{a / 2 - r, -b / 2 + r}, Point2{-a / 2 + r, -b / 2 + r}};
  vec<Point2> vp;
  vp.reserve(n);
  data_t x, y, theta;
  for (u32 i = 1; i <= n; ++i) {
    fin >> x >> y >> theta;
    Point2 c{x, y};
    for (const auto& j : d) vp.push_back(c + rot(j, theta));
  }
  ss << ConvexHull2(vp).circum() + r * PI * 2;

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "2829", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, 1) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    check(got, want, check_param(testcase));
  }
}

int main() {
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}
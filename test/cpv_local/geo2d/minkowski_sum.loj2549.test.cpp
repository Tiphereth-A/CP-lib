// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

u32 q;
strn single_proceed(std::istream& fin) {
  std::stringstream ss;

  u32 n, m;
  fin >> n >> m >> q;
  ConvexHull2 polya(n), polyb(m);
  fin >> polya >> polyb;
  for (auto& [x, y] : polyb.vs) {
    x = -x;
    y = -y;
  }
  polya.init();
  polyb.init();
  polya.do_minkowski_sum(polyb).init();
  flt_ (u32, i, 1, q + 1) {
    data_t x, y;
    fin >> x >> y;
    ss << polya.contains(Point2{x, y}) << ' ';
  }

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("loj", "2549", "war"s + data.data());
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, q) {
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
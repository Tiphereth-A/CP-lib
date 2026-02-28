// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2);

  vec<ConvexHull2> vpolys;
  int n;
  while ((fin >> n), ~n) {
    vpolys.emplace_back(n);
    fin >> vpolys.back();
    vpolys.back().init();
  }
  auto sz = vpolys.size();
  vecb destroyed(sz);
  math::kahan<data_t> destroyed_area = 0;
  Point2 missile;
  while (fin >> missile) {
    flt_ (usz, i, 0, sz)
      if (!destroyed[i] && vpolys[i].contains(missile)) {
        destroyed[i] = true;
        destroyed_area += vpolys[i].area();
      }
  }
  ss << destroyed_area << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "109", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  strn got = single_proceed(fin);
  strn want;
  std::getline(fans, want);
  while (isspace(got.back())) got.pop_back();
  while (isspace(want.back())) want.pop_back();
  check(got, want);
}

int main() {
  for (int i = 1; i <= 3; ++i) {
    timer_(test(std::to_string(i)));
  }
}
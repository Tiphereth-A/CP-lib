#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/cvh.hpp"
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
  vecb destroied(sz);
  math::kahan<data_t> destroied_area = 0;
  Point2 missile;
  while (fin >> missile) {
    flt_ (usz, i, 0, sz)
      if (!destroied[i] && vpolys[i].contains(missile)) {
        destroied[i] = true;
        destroied_area += vpolys[i].area();
      }
  }
  ss << destroied_area << '\n';

  return ss.str();
}

void test(strn CR data) {
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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::ts_example_00: test("1"); break;
    case unittest::ts_example_01: test("2"); break;
    case unittest::ts_random_00: test("3"); break;
    case unittest::ts_random_01: break;
    case unittest::ts_random_02: break;
    case unittest::ts_random_03: break;
    case unittest::ts_random_04: break;
    case unittest::ts_random_05: break;
    case unittest::ts_random_06: break;
    case unittest::ts_random_07: break;
    case unittest::ts_random_08: break;
    case unittest::ts_random_09: break;
    default: break;
  }

  unittest::post_test();
}
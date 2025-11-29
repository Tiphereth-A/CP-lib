#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo3d/cvh3d.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using point = geo::point3d<data_t>;
using cvh = geo::cvh3d<data_t>;

rand::gen<u32> g(0, 1);

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(6);

  set_eps(1e-10);
  u32 n;
  fin >> n;
  vec<point> vp(n + 1);
  flt_ (u32, i, 1, n + 1) fin >> vp[i];
  flt_ (u32, i, 1, n + 1) {
    vp[i].x += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].y += g() ? eps_v<data_t> : -eps_v<data_t>;
    vp[i].z += g() ? eps_v<data_t> : -eps_v<data_t>;
  }
  cvh cvh(vp);
  ss << cvh.surface_area() << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1209", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  g.seed();
  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got, want;
    std::getline(fans, want);
    while (isspace(want.back())) want.pop_back();
    flt_ (u32, i, 0, 16) {
      fin.seekg(0);
      got = single_proceed(fin);
      while (isspace(got.back())) got.pop_back();
      if (got == want) break;
    }
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: test("2"); break;
    case unittest::TC::random_00: test("3"); break;
    case unittest::TC::random_01: test("4"); break;
    case unittest::TC::random_02: test("5"); break;
    case unittest::TC::random_03: test("6"); break;
    case unittest::TC::random_04: test("7"); break;
    case unittest::TC::random_05: test("8"); break;
    case unittest::TC::random_06: test("9"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}
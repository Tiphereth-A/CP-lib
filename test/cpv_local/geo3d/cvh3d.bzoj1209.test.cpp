// competitive-verifier: STANDALONE

#include "../../../src/geo3d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
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
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}
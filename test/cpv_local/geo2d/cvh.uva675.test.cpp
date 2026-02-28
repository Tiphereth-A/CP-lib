// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ds/cvh/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(spn<Point2> vp) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(0);

  map<Point2, int> id;
  int cnt = 0;
  for (auto CR p : vp)
    if (!id[p]) id[p] = ++cnt;
  ConvexHull2 poly{vp};
  auto&& now = poly.vs;
  usz start = 0;
  int start_id = id[now[0]];
  flt_ (usz, i, 1, now.size())
    if (id[now[i]] < start_id) {
      start = i;
      start_id = id[now[i]];
    }
  flt_ (usz, i, start, now.size()) ss << now[i].x << ", " << now[i].y << '\n';
  flt_ (usz, i, 0, start + 1) ss << now[i].x << ", " << now[i].y << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "675", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  strn s;
  u32 testcase = 0;
  vec<Point2> vp;
  while (std::getline(fin, s))
    if (s.find(',') == strn::npos) {
    l1:;
      ++testcase;
      strn got = single_proceed(vp);
      isz cnt = std::ranges::count(got, ',');
      strn want;
      flt_ (isz, i, 1, cnt + 1) {
        strn _;
        std::getline(fans, _);
        while (isspace(_.back())) _.pop_back();
        (want += _) += '\n';
      }
      while (isspace(got.back())) got.pop_back();
      while (isspace(want.back())) want.pop_back();
      check(got, want, check_param(testcase));
      vp.clear();
      std::getline(fans, want);
    } else {
      data_t x, y;
      char ch;
      std::stringstream{s} >> x >> ch >> y;
      vp.emplace_back(x, y);
    }
  if (!vp.empty()) goto l1;
}

int main() {
  for (int i = 1; i <= 3; ++i) {
    timer_(test(std::to_string(i)));
  }
}
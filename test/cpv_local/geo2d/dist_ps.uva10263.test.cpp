// competitive-verifier: STANDALONE

#include "../../../src/geo2d/dis/ps/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;

strn single_proceed(data_t x, data_t y, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(4);

  Point2 m{x, y};
  u32 n;
  fin >> n;
  vec<Line2> l;
  l.reserve(n + 1);
  Point2 prev, now;
  fin >> prev;
  flt_ (u32, i, 1, n + 1) {
    fin >> now;
    l.emplace_back(prev, now);
    prev = now;
  }
  if (!n) {
    ss << prev.x << '\n'
       << prev.y << '\n';
    return ss.str();
  }
  data_t ans = std::numeric_limits<data_t>::max();
  Point2 ansP;
  for (auto CR i : l) {
    auto pp = geo::dist_PS_P(m, i);
    data_t d = geo::dist_PP(pp, m);
    if (is_lt(d, ans)) {
      ans = d;
      ansP = pp;
    }
  }
  ss << ansP.x << '\n'
     << ansP.y << '\n';

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "10263", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  data_t x, y;
  u32 testcase = 0;
  while (fin >> x >> y) {
    ++testcase;
    strn got = single_proceed(x, y, fin);
    strn want, want2;
    std::getline(fans, want);
    std::getline(fans, want2);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    while (isspace(want2.back())) want2.pop_back();
    want += '\n' + want2;
    check(got, want, check_param(testcase));
  }
}

int main() {
  for (int i = 1; i <= 3; ++i) {
    timer_(test(std::to_string(i)));
  }
}
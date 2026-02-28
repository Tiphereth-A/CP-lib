// competitive-verifier: STANDALONE

#include "../../../src/geo2d/ins/ll/lib.hpp"
#include "../../../src/geo2d/ins_hps/lib.hpp"
#include "../../../src/rand/gen/lib.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f128;
using Point2 = geo::point<data_t>;
using Line2 = geo::line<data_t>;
using ConvexHull2 = geo::cvh<data_t>;

strn single_proceed(std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  set_eps<data_t>(1e-20);
  u32 n;
  fin >> n;
  vec<data_t> x(n), y(n);
  for (auto& i : x) fin >> i;
  for (auto& i : y) fin >> i;
  vec<Line2> vl;
  vl.emplace_back(x.front(), -1e12, x.back(), -1e12);
  vl.emplace_back(x.back(), -1e12, x.back(), 1e12);
  vl.emplace_back(x.back(), 1e12, x.front(), 1e12);
  vl.emplace_back(x.front(), 1e12, x.front(), -1e12);
  flt_ (u32, i, 0, n - 1) vl.emplace_back(x[i], y[i], x[i + 1], y[i + 1]);
  ConvexHull2 cvh = geo::ins_hPs(vl);
  data_t ans = std::numeric_limits<data_t>::max();
  std::ranges::sort(cvh.vs, [](auto CR lhs, auto CR rhs) { return lhs.x < rhs.x; });
  u32 i = 0, j = 0;
  while (i < cvh.vs.size() && j < n) {
    if (i && is_eq(cvh[i].x, cvh[i - 1].x) && is_gt(cvh[i].y, cvh[i - 1].y)) {
      ++i;
      continue;
    }
    if (is_gt(cvh[i].x, x[j])) {
      Point2 temp = geo::ins_LL(Line2{cvh[i], cvh[i - 1]}, Line2{Point2{x[j], y[j]}, Point2{x[j], y[j] + 1}});
      ans = std::min(ans, abs(temp.y - y[j++]));
    } else {
      if (!j) {
        ++i;
        continue;
      }
      Point2 temp = geo::ins_LL(Line2{Point2{x[j - 1], y[j - 1]}, Point2{x[j], y[j]}}, Line2{cvh[i], Point2{cvh[i].x, cvh[i].y + 1}});
      ans = std::min(ans, abs(cvh[i++].y - temp.y));
    }
  }
  ss << ans;

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("bzoj", "1038", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  u32 t = 1;
  u32 testcase = 0;
  // fin >> t;
  flt_ (u32, i, 0, t) {
    ++testcase;
    strn got = single_proceed(fin);
    strn want;
    std::getline(fans, want);
    while (isspace(got.back())) got.pop_back();
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  for (int i = 1; i <= 10; ++i) {
    timer_(test(std::to_string(i)));
  }
}
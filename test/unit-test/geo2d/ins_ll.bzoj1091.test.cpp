#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/ins_ll.hpp"

#include "../../../include/geo2d/dist_pp.hpp"
#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  u32 n, m;
  fin >> n >> m;
  vec<Line2> vl;
  vl.emplace_back(0, 0, n, 0);
  vl.emplace_back(n, 0, n, m);
  vl.emplace_back(n, m, 0, m);
  vl.emplace_back(0, m, 0, 0);
  u32 p;
  fin >> p;
  vec<Point2> vp(p);
  fin >> vp;
  vl.emplace_back(vp[0], vp[p - 1]);
  flt_ (u32, i, 0, p - 1) vl.emplace_back(vp[i + 1], vp[i]);
  std::sort(vl.begin() + 4, vl.end());
  data_t ans = std::numeric_limits<data_t>::max();
  Point2 INFP{1e5, 1e5};
  do {
    data_t now_ans = 0;
    flt_ (u32, i, 4, (u32)vl.size()) {
      Point2 l = INFP, r = INFP;
      flt_ (u32, j, 0, i) {
        if (!is_ins_LL(vl[i], vl[j])) continue;
        Point2 p = ins_LL(vl[i], vl[j]);
        if (p.x < 0 || p.y < 0 || p.x > n || p.y > m) continue;
        if (!tifa_libs::is_lt(tifa_libs::geo::dist_PP(vl[i].l, p), tifa_libs::geo::dist_PP(vl[i].r, p)) && tifa_libs::is_lt(tifa_libs::geo::dist_PP(vl[i].l, p), tifa_libs::geo::dist_PP(vl[i].l, l))) l = p;
        if (!tifa_libs::is_lt(tifa_libs::geo::dist_PP(vl[i].r, p), tifa_libs::geo::dist_PP(vl[i].l, p)) && tifa_libs::is_lt(tifa_libs::geo::dist_PP(vl[i].r, p), tifa_libs::geo::dist_PP(vl[i].r, r))) r = p;
      }
      now_ans += tifa_libs::geo::dist_PP(l, r);
    }
    ans = std::min(ans, now_ans);
  } while (std::next_permutation(vl.begin() + 4, vl.end()));
  ss << ans;

  return ss.str();
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("bzoj", "1091", data);
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
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: test("2"); break;
    case tifa_libs::unittest::ts_random_00: test("3"); break;
    case tifa_libs::unittest::ts_random_01: test("4"); break;
    case tifa_libs::unittest::ts_random_02: test("5"); break;
    case tifa_libs::unittest::ts_random_03: test("6"); break;
    case tifa_libs::unittest::ts_random_04: test("7"); break;
    case tifa_libs::unittest::ts_random_05: test("8"); break;
    case tifa_libs::unittest::ts_random_06: test("9"); break;
    case tifa_libs::unittest::ts_random_07: test("10"); break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/tcenter_o.hpp"

#include "../../../include/geo2d/circle.hpp"
#include "../../../include/geo2d/is_on_same_l.hpp"
#include "../../../include/geo2d/proj.hpp"
#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Circle2 = geo::circle<data_t>;
using Triangle2 = geo::triangle<data_t>;

strn single_proceed(std::istream &fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(20);

  set_eps<data_t>(1e-9);
  u32 n;
  fin >> n;
  set<Point2> exists;
  vec<Point2> vp;
  vp.reserve(n);
  data_t x, y;
  for (u32 i = 1; i <= n; ++i) {
    fin >> x >> y;
    exists.insert(Point2{x, y});
    vp.emplace_back(x, y);
  }
  struct Comp {
    bool operator()(const Circle2 &lhs, const Circle2 &rhs) const { retif_((lhs.o == rhs.o), lhs.r < rhs.r, lhs.o < rhs.o); }
  };
  set<Circle2, Comp> circles;
  flt_ (u32, i, 0, n)
    flt_ (u32, j, i + 1, n)
      flt_ (u32, k, j + 1, n) {
        if (geo::is_on_same_L(vp[i], vp[j], vp[k])) continue;
        Triangle2 t{vp[i], vp[j], vp[k]};
        if (t.is_obtuse()) continue;
        if (t.is_right()) {
          if (is_zero(dot(vp[i], vp[j], vp[k])) && exists.find(geo::reflect({vp[j], vp[k]}, vp[i])) == end(exists)) continue;
          if (is_zero(dot(vp[j], vp[k], vp[i])) && exists.find(geo::reflect({vp[k], vp[i]}, vp[j])) == end(exists)) continue;
          if (is_zero(dot(vp[k], vp[i], vp[j])) && exists.find(geo::reflect({vp[i], vp[j]}, vp[k])) == end(exists)) continue;
        }
        circles.insert(Circle2{geo::center_O(t), geo::radius_O(t)});
      }
  data_t ans = -1;
  for (auto [o, r] : circles) {
    bool f = 0;
    for (auto CR p : vp)
      if ((f |= is_lt(geo::dist_PP(p, o), r))) break;
    if (f) continue;
    ans = std::max(ans, r);
  }
  if (ans < 0) return "-1";
  ss << ans;

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("codeforces", "274C", data);
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
    f128 got_d, want_d;
    std::from_chars(got.data(), got.data() + got.size(), got_d);
    std::from_chars(want.data(), want.data() + want.size(), want_d);
    data_t eps_prev = eps_v<data_t>;
    set_eps<data_t>(1e-4);
    check_bool(is_eq(got_d, want_d), check_param(testcase), check_param(got), check_param(want));
    set_eps<data_t>(eps_prev);
  }
}

int main() {
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"), test("13"); break;
    case unittest::TC::example_01: test("2"), test("14"); break;
    case unittest::TC::random_00: test("3"), test("15"); break;
    case unittest::TC::random_01: test("4"), test("16"); break;
    case unittest::TC::random_02: test("5"), test("17"); break;
    case unittest::TC::random_03: test("6"), test("18"); break;
    case unittest::TC::random_04: test("7"), test("19"); break;
    case unittest::TC::random_05: test("8"), test("20"); break;
    case unittest::TC::random_06: test("9"), test("21"); break;
    case unittest::TC::random_07: test("10"); break;
    case unittest::TC::random_08: test("11"); break;
    case unittest::TC::random_09: test("12"); break;
    default: break;
  }

  unittest::post_test();
}
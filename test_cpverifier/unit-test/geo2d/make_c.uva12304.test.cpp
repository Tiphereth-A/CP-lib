#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/make_c_rcc_ex.hpp"
#include "../../../include/geo2d/make_c_rll.hpp"
#include "../../../include/geo2d/make_c_rpl.hpp"
#include "../../../include/geo2d/tan_cp.hpp"
#include "../../../include/geo2d/tcenter_i.hpp"
#include "../../../include/geo2d/tcenter_o.hpp"
#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Line2 = tifa_libs::geo::line<data_t>;
using Triangle = tifa_libs::geo::triangle<data_t>;
using Circle2 = tifa_libs::geo::circle<data_t>;

CEXP data_t PI = pi_v<data_t>;

strn single_proceed(strnv s, std::istream& fin) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(6);

  if (s == "CircumscribedCircle") {
    Triangle t;
    fin >> t;
    Point2 o = center_O(t);
    data_t r = radius_O(t);
    ss << '(' << o.x << ',' << o.y << ',' << r << ")\n";
    return ss.str();
  }
  if (s == "InscribedCircle") {
    Triangle t;
    fin >> t;
    Point2 i = center_I(t);
    data_t r = radius_I(t);
    ss << '(' << i.x << ',' << i.y << ',' << r << ")\n";
    return ss.str();
  }
  if (s == "TangentLineThroughPoint") {
    Circle2 c;
    Point2 p;
    fin >> c >> p;
    auto tps = tan_CP(c, p);
    if (!tps.has_value()) {
      ss << "[]\n";
      return ss.str();
    }
    auto [tps0, tps1] = tps.value();
    Point2 d1 = Line2{p, tps0}.direction(), d2 = Line2{p, tps1}.direction();
    data_t angle1 = atan2(d1.y, d1.x) / PI * 180;
    data_t angle2 = atan2(d2.y, d2.x) / PI * 180;
    if (angle1 < 0) angle1 += 180;
    if (angle1 >= 180) angle1 -= 180;
    if (angle2 < 0) angle2 += 180;
    if (angle2 >= 180) angle2 -= 180;
    if (tifa_libs::is_eq(angle1, angle2)) {
      ss << '[' << angle1 << "]\n";
      return ss.str();
    }
    if (angle1 > angle2) std::swap(angle1, angle2);
    ss << '[' << angle1 << ',' << angle2 << "]\n";
    return ss.str();
  }
  if (s == "CircleThroughAPointAndTangentToALineWithRadius") {
    Point2 p;
    Line2 l;
    data_t r;
    fin >> p >> l >> r;
    auto cs = make_C_rPL(r, p, l);
    if (!cs.has_value()) return "[]\n";
    auto [cs0, cs1] = cs.value();
    if (cs1.o < cs0.o) std::swap(cs0, cs1);
    if (cs0.o == cs1.o) {
      ss << "[(" << cs0.o.x << ',' << cs0.o.y << ")]\n";
      return ss.str();
    }
    ss << "[(" << cs0.o.x << ',' << cs0.o.y << "),(" << cs1.o.x << ',' << cs1.o.y << ")]\n";
    return ss.str();
  }
  if (s == "CircleTangentToTwoLinesWithRadius") {
    Line2 l1, l2;
    data_t r;
    fin >> l1 >> l2 >> r;
    auto cs_ = make_C_rLL(r, l1, l2);
    if (!cs_.has_value()) return "[]\n";
    auto [cs0, cs1, cs2, cs3] = cs_.value();
    vec<Circle2> cs{cs0, cs1, cs2, cs3};
    std::ranges::sort(cs, [](Circle2 CR lhs, Circle2 CR rhs) { return lhs.o < rhs.o; });
    ss << "[(" << cs[0].o.x << ',' << cs[0].o.y << "),(" << cs[1].o.x << ',' << cs[1].o.y << "),(" << cs[2].o.x << ',' << cs[2].o.y << "),(" << cs[3].o.x << ',' << cs[3].o.y << ")]\n";
    return ss.str();
  }
  if (s == "CircleTangentToTwoDisjointCirclesWithRadius") {
    Circle2 c1, c2;
    data_t r;
    fin >> c1 >> c2 >> r;
    auto cs = make_C_rCC_ex(r, c1, c2);
    if (!cs.has_value()) {
      ss << "[]\n";
      return ss.str();
    }
    auto [cs0, cs1] = cs.value();
    if (cs1.o < cs0.o) std::swap(cs0, cs1);
    if (cs0.o == cs1.o) {
      ss << "[(" << cs0.o.x << ',' << cs0.o.y << ")]\n";
      return ss.str();
    }
    ss << "[(" << cs0.o.x << ',' << cs0.o.y << "),(" << cs1.o.x << ',' << cs1.o.y << ")]\n";
    return ss.str();
  }
  std::cout << "Unexpected s: \"" << s << "\"\n";
  exit(1);
}

void test(strn CR data) {
  auto [fn_in, fn_ans] = tifa_libs::unittest::get_fname_in_ans("uva", "12304", data);
  std::ifstream fin(fn_in), fans(fn_ans);

  strn s;
  u32 testcase = 0;
  while (fin >> s) {
    ++testcase;
    strn got = single_proceed(s, fin);
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
    case tifa_libs::unittest::ts_random_00: break;
    case tifa_libs::unittest::ts_random_01: break;
    case tifa_libs::unittest::ts_random_02: break;
    case tifa_libs::unittest::ts_random_03: break;
    case tifa_libs::unittest::ts_random_04: break;
    case tifa_libs::unittest::ts_random_05: break;
    case tifa_libs::unittest::ts_random_06: break;
    case tifa_libs::unittest::ts_random_07: break;
    case tifa_libs::unittest::ts_random_08: break;
    case tifa_libs::unittest::ts_random_09: break;
    default: break;
  }

  tifa_libs::unittest::post_test();
}
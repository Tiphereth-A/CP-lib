#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../code/geo2d/tcenter_o.hpp"

#include "../base.hpp"

using data_t = f64;
using Point2 = tifa_libs::geo::point<data_t>;
using Triangle2 = tifa_libs::geo::triangle<data_t>;

strn get_s1(char var, data_t val) {
  if (tifa_libs::is_zero(val)) return strn{var} + "^2";
  char op = tifa_libs::is_pos(val) ? '-' : '+';
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);
  ss << tifa_libs::abs(val);
  strn ret;
  ss >> ret;
  return strn{'('} + var + ' ' + op + ' ' + ret + ")^2";
}

strn single_proceed(Triangle2 CR t) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  Point2 o = tifa_libs::geo::center_O(t);
  data_t r = tifa_libs::geo::dist_PP(o, t.A);
  ss << get_s1('x', o.x) << " + " << get_s1('y', o.y) << " = " << r << "^2 ";
  ss << "x^2 + y^2 ";
  data_t F = o.x * o.x + o.y * o.y - r * r;
  char opx = o.x < 0 ? '+' : '-', opy = o.y < 0 ? '+' : '-', opF = F < 0 ? '-' : '+';
  o.x = tifa_libs::abs(o.x);
  o.y = tifa_libs::abs(o.y);
  F = tifa_libs::abs(F);
  if (!tifa_libs::is_zero(o.x)) ss << opx << ' ' << 2 * o.x << "x ";
  if (!tifa_libs::is_zero(o.y)) ss << opy << ' ' << 2 * o.y << "y ";
  if (!tifa_libs::is_zero(F)) ss << opF << ' ' << F << ' ';
  ss << "= 0  ";

  return ss.str();
}

void test(strn CR data) {
  strn path = "src/data/uva/190/" + data;
  std::ifstream fin(path + ".in"), fans(path + ".out");

  Triangle2 t;
  u32 testcase = 0;
  while (fin >> t) {
    ++testcase;
    strn got = single_proceed(t);
    while (isspace(got.back())) got.pop_back();
    strn want;
    flt_ (u32, i, 0, 3) {
      strn _;
      std::getline(fans, _);
      while (isspace(_.back())) _.pop_back();
      if (i) want += ' ';
      want += _;
    }
    while (isspace(want.back())) want.pop_back();
    check(got, want, check_param(testcase));
  }
}

int main() {
  auto tcase = tifa_libs::unittest::pre_test();

  switch (tcase) {
    case tifa_libs::unittest::ts_example_00: test("1"); break;
    case tifa_libs::unittest::ts_example_01: break;
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
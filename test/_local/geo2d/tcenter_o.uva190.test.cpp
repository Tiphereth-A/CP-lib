#define UNITTEST
#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../include/geo2d/tcenter_o.hpp"

#include "../base.hpp"

using namespace tifa_libs;
using data_t = f64;
using Point2 = geo::point<data_t>;
using Triangle2 = geo::triangle<data_t>;

strn get_s1(char var, data_t val) {
  if (is_zero(val)) return strn{var} + "^2";
  char op = is_pos(val) ? '-' : '+';
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);
  ss << abs(val);
  strn ret;
  ss >> ret;
  return strn{'('} + var + ' ' + op + ' ' + ret + ")^2";
}

strn single_proceed(Triangle2 CR t) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(3);

  Point2 o = geo::center_O(t);
  data_t r = geo::dist_PP(o, t.A);
  ss << get_s1('x', o.x) << " + " << get_s1('y', o.y) << " = " << r << "^2 ";
  ss << "x^2 + y^2 ";
  data_t F = o.x * o.x + o.y * o.y - r * r;
  char opx = o.x < 0 ? '+' : '-', opy = o.y < 0 ? '+' : '-', opF = F < 0 ? '-' : '+';
  o.x = abs(o.x);
  o.y = abs(o.y);
  F = abs(F);
  if (!is_zero(o.x)) ss << opx << ' ' << 2 * o.x << "x ";
  if (!is_zero(o.y)) ss << opy << ' ' << 2 * o.y << "y ";
  if (!is_zero(F)) ss << opF << ' ' << F << ' ';
  ss << "= 0  ";

  return ss.str();
}

void test(strnv data) {
  auto [fn_in, fn_ans] = unittest::get_fname_in_ans("uva", "190", data);
  std::ifstream fin(fn_in), fans(fn_ans);

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
  auto tcase = unittest::pre_test();

  switch (tcase) {
    case unittest::TC::example_00: test("1"); break;
    case unittest::TC::example_01: break;
    case unittest::TC::random_00: break;
    case unittest::TC::random_01: break;
    case unittest::TC::random_02: break;
    case unittest::TC::random_03: break;
    case unittest::TC::random_04: break;
    case unittest::TC::random_05: break;
    case unittest::TC::random_06: break;
    case unittest::TC::random_07: break;
    case unittest::TC::random_08: break;
    case unittest::TC::random_09: break;
    default: break;
  }

  unittest::post_test();
}
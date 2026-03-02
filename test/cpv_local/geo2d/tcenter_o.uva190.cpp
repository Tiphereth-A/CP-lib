// competitive-verifier: STANDALONE
// competitive-verifier: LOCALCASE test/cpv_local/_data/uva/190

#include "../../../src/geo2d/tcenter/o/lib.hpp"

using namespace tifa_libs;
using std::cin, std::cout;
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

int main() {
  Triangle2 t;
  while (cin >> t) {
    Point2 o = geo::center_O(t);
    data_t r = geo::dist_PP(o, t.A);
    cout << std::fixed << std::setprecision(3) << get_s1('x', o.x) << " + " << get_s1('y', o.y) << " = " << r << "^2 x^2 + y^2 ";
    data_t F = o.x * o.x + o.y * o.y - r * r;
    char opx = o.x < 0 ? '+' : '-', opy = o.y < 0 ? '+' : '-', opF = F < 0 ? '-' : '+';
    o.x = abs(o.x);
    o.y = abs(o.y);
    F = abs(F);
    if (!is_zero(o.x)) cout << opx << ' ' << 2 * o.x << "x ";
    if (!is_zero(o.y)) cout << opy << ' ' << 2 * o.y << "y ";
    if (!is_zero(F)) cout << opF << ' ' << F << ' ';
    cout << "= 0  \n";
  }
}